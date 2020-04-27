//OCW v0.91 by Will Grover (wgrover@users.sourceforge.net)
//Released under the GNU General Public License

#include <stdio.h>
#include <sys/io.h>

int main(int argc, char **argv)
{
  ioperm(atoi(argv[1]),1,1);
  outb(atoi(argv[2]),atoi(argv[1]));
  return 0;
}
