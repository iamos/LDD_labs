/* Sharing All interupts
 Extend the previous solution to a character driver that
 shares every possible interrupt with already installed handlers.

 The hightest interrupt number you have to consider will depend on your kernel and platform;
 look at /proc/interrupts to ascertain what necessary.

 Take particular care when you call free_irq() as it is very easy to freeze your system if you are not careful.

 The character driver can be very simple; for instance if no open() and release() methods are specified,
 success is the default.

 A read() on the device should return a breif report on the total number of interrpts handled for each IRQ.

 To do this you'll also have to write a short application to retreiv and print out the data.

*/

#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/slab.h> // kmalloc(), kfree()

#define MAX_IRQ 58

static int* my_dev_list;

static irqreturn_t my_handler(int irq, void *dev_id) {
	pr_info("LAB: IRQ[%d], dev_id = %d \n", irq, *(int*)dev_id);
	return IRQ_NONE;
}

static void request_all_irq(void) {
	int irq;
	/* request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
	         const char *name, void *dev)*/
	for (irq = 0; irq <= MAX_IRQ; irq++) {
		my_dev_list[irq] = -1;
		// if( (request_irq(irq, my_handler, IRQF_SHARED, "my_handler", my_dev_list+(sizeof(int)*irq))) != 0){
		if ( (request_irq(irq, my_handler, IRQF_SHARED, "my_handler", &my_dev_list[irq])) != 0) {
			my_dev_list[irq] = 0;
			pr_info("Succeded in registering IRQ=%d\n", irq);
		}
	}
}
static void free_all_handler(void) {
	int irq;
	for (irq = 0; irq <= MAX_IRQ; irq++) {
		if (my_dev_list[irq] > 0) {
			synchronize_irq(irq);
			// free_irq(irq, my_dev_list+(sizeof(int)*irq));
			free_irq(irq, &my_dev_list[irq]);
			pr_info("FREE: irq[%d], %d\n", irq, my_dev_list[irq]);
		}
	}
}

static int __init my_init(void) {
	my_dev_list = kmalloc(sizeof(int) * MAX_IRQ, GFP_KERNEL);
	pr_info("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\nLAB: Statrt loading ISR handler\n");
	request_all_irq();
	pr_info("\nLAB: loading ISR handler\n");
	return 0;
}

static void __exit my_exit(void) {
	/*synchronize_irq(keyboard_irq);
	free_irq(keyboard_irq, &my_dev_id);*/
	free_all_handler();
	kfree(my_dev_list);
	pr_info("\nLAB: Successfully unloading \n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Oseok");
MODULE_LICENSE("GPL v2");