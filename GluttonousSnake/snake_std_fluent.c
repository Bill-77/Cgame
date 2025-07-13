#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable : 4996)
#define W 28
#define H W
#define S (W * H)

void set_cursor(int x, int y) {
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_at(int r, int c, const char *ch) {
	set_cursor(c * 2, r);
	printf("%s", ch);
}

int main() {
	char o[S * 2 + W + 3], *c = o;
	int m[S + 1], q[S], l = 0, r = 4, d = 1, p, a, i;
	for (i = l; i <= r; ++i) q[i] = S;
	for (i = 0; i < S; c += 2, ++i % W || (*c++ = '\n')) {
		m[i] = !(i / W % (H - 1) && i % W % (W - 1));
		m[i] ? (*c = '[', c[1] = ']') : (*c = c[1] = ' ');
	}
	p = W / 2 * (H + 1) - d, a = p + d, o[S * 2 + W + 2] = '\0';
	system("cls");
	printf("%s", o);
	print_at(a / W, a % W, "00");
	for (srand((unsigned)time(0)); i = 1; _sleep(100)) {
		if (_kbhit() && (i = _getch() & 95)) {
			if (i == 'A' && d != 1) d = -1;
			else if (i == 'D' && d != -1) d = 1;
			else if (i == 'W' && d != W) d = -W;
			else if (i == 'S' && d != -W) d = W;
		}
		int t = p;
		p += d;
		if (m[p] && p != q[l + 1] || i == 27) {
			printf("Game over!\n");
			_sleep(1000);
			break;
		}
		if (p == a) {
			for (a = rand() % S; m[a]; a = (a + 1) % S) {}
			print_at(a / W, a % W, "00");
			*(c = o + a * 2 + a / W) = '0', c[1] = '0';
		} else {
			m[i = q[l = (l + 1) % S]] = 0;
			print_at(i / W, i % W, "  ");
			*(c = o + i * 2 + i / W) = ' ', c[1] = ' ';
		}
		m[q[r] = p] = 1, r = (r + 1) % S;
		print_at(p / W, p % W, "()");
		*(c = o + p * 2 + p / W) = '(', c[1] = ')';
	}
}
