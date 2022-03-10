#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_DESCRIPTION("List current processes");
MODULE_AUTHOR("Kernel Hacker");
MODULE_LICENSE("GPL");

static int my_proc_init(void)
{
	struct task_struct *p;

    // https://www.humblec.com/retrieving-current-processtask_struct-in-linux-kernel/
    p = get_current();

	/* TODO: print current process pid and its name */
    pr_info("PID: %d; Proc. Name: %s\n", p->pid, p->comm);

	/* TODO: print the pid and name of all processes */
    // https://stackoverflow.com/questions/939778/linux-api-to-list-running-processes
    for_each_process(p) {
        pr_info("PID: %d; Proc. Name: %s\n",p->pid , p->comm);
    }   

	return 0;
}

static void my_proc_exit(void)
{
    struct task_struct *p;

	/* TODO: print current process pid and name */
    p = get_current();
    pr_info("PID: %d; Proc. Name: %s\n", p->pid, p->comm);

}

module_init(my_proc_init);
module_exit(my_proc_exit);
