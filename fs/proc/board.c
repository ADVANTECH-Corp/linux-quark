#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

char board_type[20];

static int board_proc_show(struct seq_file *m, void *v)
{
#ifdef CONFIG_UBC221
	strcpy(board_type, "UBC-221");
#endif
#ifdef CONFIG_UBC222
	strcpy(board_type, "UBC-222");
#endif
	seq_printf(m, "%s", board_type);
	return 0;
}

static int board_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, board_proc_show, NULL);
}

static const struct file_operations board_proc_fops = {
	.open		= board_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_board_init(void)
{
	proc_create("board", 0, NULL, &board_proc_fops);
	return 0;
}
module_init(proc_board_init);
