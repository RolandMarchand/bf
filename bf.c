/*
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

#define VM_SIZE 30000

/* move the ip to the next cell
 * value is clamped to the last cell */
#define INC (vm.ip = (vm.ip + 1 >= vm.data + VM_SIZE)	\
	     ? vm.data + VM_SIZE - 1			\
	     : vm.ip + 1)
/* move the ip to the previous cell
 * value is clamped to the starting cell */
#define DEC (vm.ip = (vm.ip - 1 < vm.data) ? vm.data : vm.ip - 1)
/* increment the value of the current cell */
#define PLUS (++*vm.ip)
/* decrement the value of the current cell */
#define MINUS (--*vm.ip)
/* write the value of the current cell to stdout */
#define GET (putchar(*vm.ip))
/* read one byte of data from stdin */
#define SET (*vm.ip = getchar())

struct vm {
	char *ip;
	char data[VM_SIZE];
};

struct vm vm = (struct vm){.data = {0}, .ip = vm.data};
FILE *source;

/* computes the current command and jump to the next
 * return 0 if the command was successful
 * return 1 if reached EOF*/
int get();
/* return 1 if the file's brackets match and are in the right order
 * return 0 they do not */
int check_file();
/* go to the command after the next matching bracket */
void next_bracket();
/* go to the command after the previous matching bracket */
void previous_bracket();

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: ./bf [source.bf]\n");
		return 1;
	}

	if (!(source = fopen(argv[1], "r"))) {
		fprintf(stderr, "File '%s' does not exist.\n", argv[1]);
		return 2;
	}

	if (!check_file()) {
		fprintf(stderr, "Unbalanced brackets.\n");
		return 3;
	}

	int result;
loop:
	result = get();
	if (result) return result;
	goto loop;
}

int get()
{
skip:
	switch (fgetc(source)) {
	case '>': INC; break;
	case '<': DEC; break;
	case '+': PLUS; break;
	case '-': MINUS; break;
	case ',': SET; break;
	case '.': GET; break;
	case '[': if (!*vm.ip) next_bracket(); break;
	case ']': if (*vm.ip) previous_bracket(); break;
	case EOF: return 1;
	default: goto skip; /* everything else is a comment */
	}

	return 0;
}

int check_file()
{
	int stack = 0;
	char c;

	while ((c = fgetc(source)) != EOF) {
		stack += c == '[';
		stack -= c == ']';
		if (stack < 0) return 0;
	}

	fseek(source, 0, SEEK_SET);
	return stack == 0;
}

void next_bracket()
{
	int stack = 1;
	char c;
loop:
	c = fgetc(source);

	stack += c == '[';
	stack -= c == ']';

	if (stack == 0) {
		return;
	}

	goto loop;
}

void previous_bracket()
{
	int stack = 1;
	char c;
loop:
	fseek(source, -2, SEEK_CUR);
	c = fgetc(source);

	stack += c == ']';
	stack -= c == '[';

	if (stack == 0) {
		return;
	}

	goto loop;
}
