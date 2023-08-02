#include <linux/init.h>

#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/netfilter.h>

#include <linux/netfilter_ipv4.h>

#include <linux/ip.h>

#include <linux/icmp.h>


MODULE_LICENSE("GPL");

MODULE_AUTHOR("Bezalel Yehuda");

MODULE_DESCRIPTION("Kernel module to drop ping packets and print src and dest IPs");

MODULE_VERSION("0.01");


static struct nf_hook_ops *nfho = NULL; //struct containing behavior to register to netfilter hook.


// hook function

static int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)

{

struct iphdr *iph; // struct to read ip header info from buffer

struct icmphdr *icmph; // struct to read icmp header info from buffer

unsigned int src_ip;

unsigned int dest_ip;


if (!skb) // bufffer is empty, not a ping message - accept packet

return NF_ACCEPT;


iph = ip_hdr(skb); // extract ip header info from buffer

if (iph->protocol != IPPROTO_ICMP) // accept all packets that are not using ICMP protocol

return NF_ACCEPT;


icmph = icmp_hdr(skb); // extract icmp header info from buffer

if (icmph->type != ICMP_ECHO) // accept all ICMP messages that are not ICMP ECHO messages

return NF_ACCEPT;


src_ip = (unsigned int)iph->saddr; //source ip address

dest_ip = (unsigned int)iph->daddr; // destination ip address

printk(KERN_INFO "Dropping ping packet. src: %pI4 dest: %pI4\n", &src_ip, &dest_ip);


return NF_DROP; // drop ping messages

}


static int __init LKM_init(void)

{

// define behaviour for netfilter hook

nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);

nfho->hook = (nf_hookfn*)hfunc; /// set earlier func as hook func

nfho->hooknum = NF_INET_PRE_ROUTING; // define hook timing

nfho->pf = PF_INET; // define protocol

nfho->priority = NF_IP_PRI_FIRST; // define max priority for rule.


nf_register_net_hook(&init_net, nfho); // register the hook behaviour.


return 0;

}


static void __exit LKM_exit(void)

{

nf_unregister_net_hook(&init_net, nfho); // unregister the hook

kfree(nfho);

}


module_init(LKM_init);
module_exit(LKM_exit);
