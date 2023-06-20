#include <stdio.h>
#define W_INDEX 0
#define H_INDEX 1
#define T_INDEX 2
#define P_INDEX 3
#define S_INDEX 4
#define A_INDEX 5
#define N_INDEX 6

int main(int argc, char const *argv[])
{
	int wall[100000];
	int wall_r, count_k, tribe_w, tribe_h, tribe_t, tribe_p, tribe_s, tribe_a, tribe_n;
	int i, j, k;
	for (i = 0; i < 100000; ++i)
	{
	    wall[i] = 1;
	}
	scanf("%d\n%d\n", &wall_r, &count_k);
	for (i = 0; i < count_k; ++i)
	{
		scanf("%d %d %d %d %d %d %d\n", &tribe_w, &tribe_h, &tribe_t, &tribe_p, &tribe_s, &tribe_a, &tribe_n);
		for (j = 0; j < tribe_n; ++j)
		{
			for (k = tribe_p; k < (tribe_p + tribe_w); ++k)
			{
				if ( k > wall_r || k < 0) {
					continue;
				}
				else
				{
				    if (wall[k] < tribe_h){
				    	wall[k] = tribe_h;
				    }
				}
			}
			tribe_p = tribe_p + tribe_s * tribe_a;
		}
	}
	for (i = 0; i < wall_r; ++i)
	{
		printf("%d ", wall[i]);
	}
	printf("%d\n", wall[wall_r]);
	return 0;
}