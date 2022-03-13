/*
 * SO2 lab3 - task 3
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_DESCRIPTION("Memory processing");
MODULE_AUTHOR("SO2");
MODULE_LICENSE("GPL");

struct task_info {
	pid_t pid;
	unsigned long timestamp;
};

static struct task_info *ti1, *ti2, *ti3, *ti4;

static struct task_info *task_info_alloc(int pid)
{
	struct task_info *ti;

	/* TODO 1: allocated and initialize a task_info struct */
	ti = kmalloc(sizeof(struct task_info), GFP_KERNEL);
	if (!ti) {
		printk(KERN_ERR "Cannot malloc task_info struct");
		return NULL;
	}

	ti->pid = pid;
	ti->timestamp = jiffies;

	return ti;
}

static int memory_init(void)
{
	struct task_struct *p1, *p3, *p4;
	/* TODO 2: call task_info_alloc for current pid */
	p1 = get_current();
	ti1 = task_info_alloc(p1->pid);

	/* TODO 2: call task_info_alloc for parent PID */
	ti2 = task_info_alloc(p1->parent->pid);

	/* TODO 2: call task_info alloc for next process PID */
	p3 = next_task(p1);
	ti3 = task_info_alloc(p3->pid);

	/* TODO 2: call task_info_alloc for next process of the next process */
	p4 = next_task(next_task(p1));
	ti4 = task_info_alloc(p4->pid);

	return 0;
}

static void memory_exit(void)
{

	/* TODO 3: print ti* field values */
	pr_info("ti1: pid: %d timestamp: %lx\n", ti1->pid, ti1->timestamp);
	pr_info("ti2: pid: %d timestamp: %lx\n", ti2->pid, ti2->timestamp);
	pr_info("ti3: pid: %d timestamp: %lx\n", ti3->pid, ti3->timestamp);
	pr_info("ti4: pid: %d timestamp: %lx\n", ti4->pid, ti4->timestamp);


	/* TODO 4: free ti* structures */
	kfree(ti1);
	kfree(ti2);
	kfree(ti3);
	kfree(ti4);
}

module_init(memory_init);
module_exit(memory_exit);
