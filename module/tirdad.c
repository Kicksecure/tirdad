/*
    By Sirus Shahini
    ~cyn
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/random.h>
#include <linux/livepatch.h>
#include <linux/version.h>
#include <net/net_namespace.h>

#ifdef COLORED_OUTP
#define CNORM				"\x1b[0m"
#define CRED				"\x1b[1;31m"
#define CGREEN				"\x1b[1;32m"
#else
#define CNORM				""
#define CRED				""
#define CGREEN				""
#endif

void _s_out(u8 err, char *fmt, ...);

int hook_init(void);
void hook_exit(void);


void _s_out(u8 err, char *fmt, ...){
	va_list argp;
	char msg_fmt[255];

	if (err){
		snprintf(msg_fmt, 255, CRED"[!] TIRDAD: "CNORM"%s\n", fmt);
	}else{
		snprintf(msg_fmt, 255, CGREEN"[-] TIRDAD: "CNORM"%s\n", fmt);
	}

	va_start(argp,fmt);
	vprintk(msg_fmt,argp);
	va_end(argp);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 18, 17)

u32 secure_tcp_seq_hooked(__be32 , __be32 , __be16 , __be16 );
u32 secure_tcpv6_seq_hooked(const __be32 *, const __be32 *,__be16 , __be16 );
u32 get_isn(void);

u32 get_isn(){
	u32 hash;
	get_random_bytes(((u8 *)&hash), sizeof(u32));
	return hash;
}

u32 secure_tcp_seq_hooked(__be32 saddr, __be32 daddr,
	__be16 sport, __be16 dport)
{
	return get_isn();
}


u32 secure_tcpv6_seq_hooked(const __be32 *saddr, const __be32 *daddr,
	__be16 sport, __be16 dport)
{
	return get_isn();
}

#define	V4_KERNEL_SYM	"secure_tcp_seq"
#define V4_HOOK_FUNC	secure_tcp_seq_hooked

#define	V6_KERNEL_SYM	"secure_tcpv6_seq"
#define V6_HOOK_FUNC	secure_tcpv6_seq_hooked

#else

u64 secure_tcp_seq_and_ts_off_hooked(const struct net *, __be32 , __be32 , __be16 , __be16 );
u64 secure_tcpv6_seq_and_ts_off_hooked(const struct net *, const __be32 *, const __be32 *,__be16 , __be16 );
u64 get_isn_ts(const struct net *);

union tcp_seq_and_ts_off {
	struct {
		u32 seq;
		u32 ts_off;
	};
	u64 hash64;
};

u64 get_isn_ts(const struct net *net){
	union tcp_seq_and_ts_off seq_ts;

	seq_ts.ts_off = 0;

	get_random_bytes(((u8 *)&(seq_ts.seq)), sizeof(u32));

	if (READ_ONCE(net->ipv4.sysctl_tcp_timestamps) == 1)
		get_random_bytes(((u8 *)&(seq_ts.ts_off)), sizeof(u32));

	return seq_ts.hash64;
}

u64 secure_tcp_seq_and_ts_off_hooked(const struct net *net, __be32 saddr, __be32 daddr,
	__be16 sport, __be16 dport)
{
	return get_isn_ts(net);
}


u64 secure_tcpv6_seq_and_ts_off_hooked(const struct net *net, const __be32 *saddr, const __be32 *daddr,
	 __be16 sport, __be16 dport)
{
	return get_isn_ts(net);
}

#define	V4_KERNEL_SYM	"secure_tcp_seq_and_ts_off"
#define V4_HOOK_FUNC	secure_tcp_seq_and_ts_off_hooked

#define	V6_KERNEL_SYM	"secure_tcpv6_seq_and_ts_off"
#define V6_HOOK_FUNC	secure_tcpv6_seq_and_ts_off_hooked

#endif

static struct klp_func funcs[] = {
 	{
		.old_name = V4_KERNEL_SYM,
		.new_func = V4_HOOK_FUNC,
	},
	{
		.old_name = V6_KERNEL_SYM,
		.new_func = V6_HOOK_FUNC,
	}, { }
};

static struct klp_object objs[] = {
	{
	.funcs = funcs,
	}, { }
};

static struct klp_patch patch = {
	.mod = THIS_MODULE,
	.objs = objs,
};

int hook_init(void){
#if !IS_ENABLED(CONFIG_IPV6)

	/*
	 *	A fail-safe for an extremely unlikely situation.
	 *	If you have a strange custom kernel without IPv6 support,
	 *	revert to the older versions of tirdad (like commit: 1742ca6).
	*/

	_s_out(1,"IPv6 is not supported in your system.");
	return -1;
#endif

	/*
	 *	Ensure RNG is initialized
	 */

	if (wait_for_random_bytes()){
		_s_out(1,"FATAL: Can't get random bytes from kernel.");
		return -1;
	}

	/*
	 *	Install the hooks
	 */

	_s_out(0, "Installing ISN hooks...");
	if (! klp_enable_patch(&patch)){
		_s_out(0, "Hooks ready.");
		return 0;
	}
	else{
		_s_out(1, "Installation failed");
		return -1;
	}
}

void hook_exit(void){
	_s_out(0,"Removed hooks. Exiting normally.");
}

module_init(hook_init);
module_exit(hook_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sirus Shahini <sirus.shahini@gmail.com>");
MODULE_DESCRIPTION("Tirdad hook for TCP ISN generator");
MODULE_INFO(livepatch, "Y");

