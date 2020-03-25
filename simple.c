#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
 struct birthday{
       int day;
       int month;
       int year;
       struct list_head list;
};

static LIST_HEAD(birthday_list);
/* This function is called when the module is loaded. */
int simple_init(void)
{
       struct birthday *person;
       struct birthday *person2;
       struct birthday *person3;
       struct birthday *person4;
       struct birthday *person5;
       struct birthday *ptr;

       person = kmalloc(sizeof(*person), GFP_KERNEL);
       person->day = 2;
       person->month = 8;
       person->year = 1995;
       INIT_LIST_HEAD(&person->list);
       list_add_tail(&person->list, &birthday_list);
       
       person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
       person2->day = 3;
       person2->month = 4;
       person2->year = 1999;
       INIT_LIST_HEAD(&person2->list);
       list_add_tail(&person2->list, &birthday_list);

       person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
       person3->day = 6;
       person3->month = 11;
       person3->year = 2003;
       INIT_LIST_HEAD(&person3->list);
       list_add_tail(&person3->list, &birthday_list);

       person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
       person4->day = 15;
       person4->month = 9;
       person4->year = 1974;
       INIT_LIST_HEAD(&person4->list);
       list_add_tail(&person4->list, &birthday_list);

       person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
       person5->day = 27;
       person5->month = 3;
       person5->year = 1982;
       INIT_LIST_HEAD(&person5->list);
       list_add_tail(&person5->list, &birthday_list);


       list_for_each_entry(ptr,&birthday_list,list){
              printk(KERN_INFO "Date: %d/%d/%d",ptr->day,ptr->month,ptr->year);
       }
       
       printk(KERN_INFO "Loaded Module\n");
       printk(KERN_INFO "\n\n");
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
       struct birthday *ptr,*next;
       int i = 1;

       printk(KERN_INFO "List before Delete:");
       
       list_for_each_entry(ptr,&birthday_list,list){
              printk(KERN_INFO "Date: %d/%d/%d",ptr->day,ptr->month,ptr->year);
       }

       list_for_each_entry_safe(ptr,next,&birthday_list,list){
              list_del(&ptr->list);
              kfree(ptr);
              printk(KERN_INFO "removed element:%d",i);
              i++;
       }
       printk(KERN_INFO "List after Delete:");

       list_for_each_entry(ptr,&birthday_list,list){
              printk(KERN_INFO "Date: %d/%d/%d",ptr->day,ptr->month,ptr->year);
              
       }
       printk(KERN_INFO "\n");
	printk(KERN_INFO "Removed Module\n");
       printk(KERN_INFO "\n\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

