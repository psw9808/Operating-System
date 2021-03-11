#include <linux/kernel.h>
#include <linux/module.h>

int hello_module_init(void){
	printk("<1>Hello Module~!\n");
	return 0;
}

void hello_module_cleanup(void){
	printk("<1>Bye Module~!\n");	
}

module_init(hello_module_init);
module_exit(hello_module_cleanup);

MODULE_LICENSE("GPL");

