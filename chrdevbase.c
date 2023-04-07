#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>

#define CHRDEVBASE_MAJOR		200				/*主设备号*/
#define CHRDEVBASE_NAME			"chrdevbase"	/*设备名*/

static char readbuf[100];		/*读缓冲区*/
static char writebuf[100];		/*写缓冲区*/
static char kerneldata[] = {"kernel data!"};

/*打开设备
  inode:传递给驱动的inode
  filp:设备文件,file结构体有个叫private_data的成员变量,一般在
	   open的时候将private_data指向设备结构体
*/
static int charderbase_open(struct inode *inode,struct file *filp)
{
	return 0;
}


/*从设备读取书籍
  filp:要打开的设备文件(文件描述符)
  buf:返回给用户空间的数据缓冲区
  cnt:要读取的数据长度
  offt:相对于文件首地址的偏移
  return:读取的字节数,如果为负值,表示读取失败
*/
static ssize_t chrdevbase_read(struct file *filp,char __user *buf,size_t cnt,lofft *offt)
{
	int retvalue = 0;
	/*向用户空间发送数据*/
	memcpy(readbuf,kerneldata,sizeof(kerneldata));
	retvalue = copy_to_user(buf,readbuf,cnt);
	if(retvalue == 0)
	{
		printk("Kernel senddata ok!\r\n");
	}
	else
	{
		printk("kernel senddata failed!\r\n");
	}
	return 0;
}


/*向设备写数据
  filp:设备文件,表示打开的文件描述符
  buf:要写给设备的数据
  cnt:要写入的数据长度
  offt:相对于文件首地址的偏移
  return:写入的字节数,如果为负值,表示写入失败
*/
static ssize_t chrdevbase_write(struct file *filp,const char __user *buf,size_t cnt,loff_t *offt)
{
	int retvalue = 0;
	/*接收用户空间传递给内核的数据*/
	retvalue = copy_from_user(writebuf,buf,cnt);
	if(retvalue == 0)
	{
		printk("kernel recevdata:%s\r\n",writebuf);
	}
	else
	{
		printk("kernel recevdata failed!\r\n");
	}
	return 0;
}


/*关闭/释放设备
  filp:要关闭的设备文件
  return: 0成功,其他 失败
*/
static int chrdevbase_release(struct inode *inode,struct file *filp)
{
	return 0;
}


/*设备操作函数结构体
*/
static struct file_operations chrdevbase_fops = {
	.owner = THIS_MODULE,
	.open = chrdevbase_open,
	.read = chrdevbase_read,
	.write = chrdevbase_write,
	.release = chrdevbase_release,
};

/*驱动入口函数
  return 0成功,其他 失败
*/
static int __init chrdevbase_init(void)
{
	int retvalue = 0;
	/*注册字符设备驱动*/
	retvalue = register_chrdev(CHRDEVBASE_MAJOR,CHRDEVBASE_NAME,&chrdevbase_fops);
	if(retvalue < 0)
	{
		printk("chrdevbase driver register failed\r\n");
	}
	else
	{
		printk("chrdevbase driver register failed\r\n");
	}
	printk("chrdevbase_init()\r\n");
	return 0;
}

/*驱动出口函数
*/
static void __exit chrdevbase_exit(void)
{
	/*注销字符设备驱动*/
	unregister_chrdev(CHRDEVBASE_MAJOR,CHRDEVBASE_NAME);
	printk("chrdevbase_exit()\r\n");
}

/*将上面两个函数指定为驱动的入口和出口函数
*/
module_init(chrdevbase_init);
module_exit(chrdevbase_exit);


/*LICENSE和作者信息*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XIAOHU");
MODULE_INFO(intree,"Y");