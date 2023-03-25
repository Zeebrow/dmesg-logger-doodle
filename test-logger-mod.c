#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>// Module metadata
#include <linux/string.h>

// See Ruan de Bruyn's excellent article on Medium:
// https://medium.com/dvt-engineering/how-to-write-your-first-linux-kernel-module-cf284408beeb
MODULE_LICENSE("GPL");
MODULE_AUTHOR("zeebrow");
MODULE_DESCRIPTION("interject into an otherwise civilized dmesg discussion");

const char m[] = "test_logger_mod: I'd just like to interject for a moment.\nWhat you're refering to as Linux, is in fact, GNU/Linux, or as I've recently taken to calling it, GNU plus Linux.\nLinux is not an operating system unto itself, but rather another free component of a fully functioning GNU system made useful by the GNU corelibs, shell utilities and vital system components comprising a full OS as defined by POSIX.\nMany computer users run a modified version of the GNU system every day, without realizing it.\nThrough a peculiar turn of events, the version of GNU which is widely used today is often called Linux, and many of its users are not aware that it is basically the GNU system, developed by the GNU Project.\nThere really is a Linux, and these people are using it, but it is just a part of the system they use.\nLinux is the kernel: the program in the system that allocates the machine's resources to the other programs that you run.\nThe kernel is an essential part of an operating system, but useless by itself; it can only function in the context of a complete operating system.\nLinux is normally used in combination with the GNU operating system: the whole system is basically GNU with Linux added, or GNU/Linux.\nAll the so-called Linux distributions are really distributions of GNU/Linux!\n";

static struct proc_dir_entry* proc_entry;

	//ssize_t	(*proc_write)(struct file *, const char __user *, size_t, loff_t *);
static ssize_t custom_write(struct file* file, const char __user* user_buffer, size_t count, loff_t* offset)
{
	printk(KERN_INFO "you wrote to a file!");
  int len_of_write = strlen(user_buffer);

	return len_of_write;
}

/*
This function gets called a lot.
I am guessing when a user space program needs to call `read`, it will continue to do so until this function returns 0.
*/
static ssize_t custom_read(struct file* file, char __user* user_buffer, size_t count, loff_t* offset)
{

  //char greeting[] = "hi!\n";
  //int greeting_length = strlen(greeting);
  int greeting_length = strlen(m);

	printk(KERN_INFO "test_logger_mod: calling our very own custom read method.");
	//printk(KERN_INFO "%s", m);

  //copy_to_user(user_buffer, greeting, greeting_length);
  copy_to_user(user_buffer, m, greeting_length);

  // ???
	if (*offset > 0)
		return 0;

	*offset = greeting_length;

	return greeting_length;
}

// Custom init and exit methods  for kernel version >= 5.6
// https://stackoverflow.com/a/64932529
// You'll need to replace his `file_operations` struct with a `proc_ops`
// (proc_fs.h) if you're following along in 2023 and beyond:
static struct proc_ops pops = 
{
  .proc_read = custom_read,
  .proc_write = custom_write
};

static int __init custom_init(void) {

	//struct proc_dir_entry *proc_create(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct proc_ops *proc_ops);
	proc_entry = proc_create("test_logger_mod", 0666, NULL, &pops);

	printk(KERN_INFO "test_logger_mod: init: %s", m);
//	printk(KERN_INFO "%s", m1);
//	printk(KERN_INFO "%s", m2);
//	printk(KERN_INFO "%s", m3);
//	printk(KERN_INFO "%s", m4);
//	printk(KERN_INFO "%s", m5);
//	printk(KERN_INFO "%s", m6);
//	printk(KERN_INFO "%s", m7);
//	printk(KERN_INFO "%s", m8);
//	printk(KERN_INFO "%s", m9);
//	printk(KERN_INFO "%s", m10);
	return 0;
}

static void __exit custom_exit(void) {
	proc_remove(proc_entry);
	printk(KERN_INFO "test_logger_mod: exit: Goodbye my friend, I shall miss you dearly...");
}

module_init(custom_init);
module_exit(custom_exit);
