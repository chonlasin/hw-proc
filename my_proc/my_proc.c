#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_FILENAME "my_proc"

static char message[256] = {0};
static struct proc_dir_entry *proc_entry;

static ssize_t my_proc_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset) {
    return simple_read_from_buffer(buffer, length, offset, message, strlen(message));
}

static ssize_t my_proc_write(struct file *filp, const char __user *buffer, size_t length, loff_t *offset) {
    return simple_write_to_buffer(message, sizeof(message), offset, buffer, length);
}

static const struct proc_ops my_proc_fops = {
    .proc_read = my_proc_read,
    .proc_write = my_proc_write,
};

static int __init my_init(void) {
    proc_entry = proc_create(PROC_FILENAME, 0666, NULL, &my_proc_fops);
    if (!proc_entry) {
        printk(KERN_ERR "Failed to create proc entry\n");
        return -ENOMEM;
    }
    printk(KERN_INFO "Proc entry created\n");
    return 0;
}

static void __exit my_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
    printk(KERN_INFO "Proc entry removed\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("uyc");
MODULE_DESCRIPTION(" kernel module  /proc ");
