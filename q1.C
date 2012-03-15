#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long integer;

static void print_vector(const char *label, integer start, integer lastp1, integer *data) __attribute__ ((unused));
static void print_vector(const char *label, integer start, integer lastp1, integer *data) {
	printf("%s = [",label);
	for (integer i = start; i < lastp1; ++i) {
		if (i != start) printf(", ");
		printf("%ld",data[i]);
	}
	printf("]\n");
}

static integer count_split_inversions(integer start, integer lastp1, integer *data) {
	integer count = 0;
	if ((lastp1 - start) > 1) {
		integer mid = start + (lastp1-start) / 2;

		integer a = count_split_inversions(start,mid,data);
		integer b = count_split_inversions(mid, lastp1, data);
		integer c = 0;
// Now we weave them together.
		integer apos = start, bpos = mid;

		integer tempsz = 0;
		integer temp[lastp1-start];
/*
a = [54044]
b = [14108, 79294]
temp = [14108, 54044, 14108, 79294]

apos=0
bpos=0
temp=[] -> [14108]
apos=1
bpos=0
temp=[14108] -> [14108,54044]
apos=1
bpos=1

 */
		while ((apos < mid) || (bpos < lastp1)) {
			if ((bpos >= lastp1) || ((apos < mid) && (data[apos] < data[bpos]))) {
				temp[tempsz++] = data[apos++];
			}
			else {
				temp[tempsz++] = data[bpos++];
				// The rest of a's are inversions.
				c += (mid - apos);
			}
		}

		assert(tempsz == (lastp1-start));
		for (integer i = 0; i < tempsz; ++i) data[start+i] = temp[i];

		count = a + b + c;
	}
	return(count);
}

int main(int argc,char *argv[]) {
	integer datasz = 0;
	integer data[100000];
	FILE *fp = fopen("q1data.txt","r");
	if (fp) {
		char buffer[1024];
		while (fgets(buffer,1024,fp) != NULL) {
			data[datasz++] = atoi(buffer);
		}
		fclose(fp); fp = NULL;

		integer s = count_split_inversions(0,datasz,data);
		printf("%ld\n",s);
	}
	return(0);
}
