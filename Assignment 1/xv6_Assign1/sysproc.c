#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

//declaring utility for part 3 of assignment, definition in proc.c since defs.h cannot be modified
extern void get_pid_name(void);

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//Part 1b begins
int systrace_mode;

int
sys_toggle(void)
{
  systrace_mode = 1-systrace_mode;
  return 0;
}

int
check_systrace(void) //Not a syscall
{
  if(systrace_mode == 0)
    return 1;
  return 0;
}
//Part 1b ends


//Part 2 begins
int
sys_add(int a, int b)
{
  argint(0, &a);
  argint(1, &b);
  return a+b;
}
//Part 2 ends


//Part 3 begins
int
sys_ps(void)
{
  //your code goes here
  get_pid_name();
  return 0;
}
//Part 3 ends