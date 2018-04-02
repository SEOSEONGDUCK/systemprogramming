#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

#define buffer_length 256

char msg[buffer_length];

int simple_open (struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "open simple char drv\n");
  return 0;
}
ssize_t simple_read(struct file *pfile, char __user *buffer,size_t length, loff_t *offset)
{
  printk("Read simple char drv\n");
  if(strcmp(msg,"test") ==0)
    copy_to_user(buffer,"GET TEST",buffer_length);
  else
    copy_to_user(buffer,"NOT TEST",buffer_length);
  return 0;
}
ssize_t simple_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  printk("Write simple char drv\n");
  if(copy_from_user(msg,buffer,buffer_length) < 0){
    printk("Write error\n");
    return -1;
  }
  return length;
}
int simple_close(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "release simple char drv\n");
  return 0;
}

struct file_operations fop ={
	.owner =THIS_MODULE,
	.open =simple_open,
	.read =simple_read,
	.write =simple_write,
	.release =simple_close,
};

int __init simple_init(void)
{
  printk(KERN_ALERT "init simple char drv\n");
  register_chrdev(240, // major number
		"simple char drv",// Driver name
		&fop);
  return 0;
}
void __exit simple_exit(void)
{
  printk(KERN_ALERT "Exit simple char drv\n");
  unregister_chrdev(240,"Simple char drv");
}
module_init(simple_init);
module_exit(simple_exit);
