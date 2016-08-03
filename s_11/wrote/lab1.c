/*Lab1. Kernel Timers from a Character Driver
	Write a driver that puts launches a kernel timer whenever a write() to the device takes place.
	Pass some data to the driver and have it print out.
	Have it print out the current->pid field when the timer function is scheduled, and then again when
		the function is executed.
*/
#include <linux/timer.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>

static int chardev_open(struct inode* inode, struct file* file) {

}

static int chardev_release(struct inode* inode, struct file* file) {

}

static ssize_t chardev_read(struct file* file, char __user* buf, size_t lbuf, loff_t* ppos) {

}

static ssize_t chardev_write(struct file *file, const char __user * buf, size_t lbuf, loff_t * ppos) {

}

static inline loff_t chardev_lseek(struct file *file, loff_t offset, int orig) {

}

static const struct file_operations chardev_fops = {
	.owner = THIS_MODULE,
	.read = chardev_read,
	.write = chardev_write,
	.open = chardev_open,
	.release = chardev_release,
};

static int __init my_init(void) {
	return 0;
}

static void __exit my_exit(void) {

}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");