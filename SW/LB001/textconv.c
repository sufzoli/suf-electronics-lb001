/*
void LongToBCD(unsigned int len, unsigned char str[], unsigned long src, unsigned char leadingzero)
{
	unsigned long tmp;

	unsigned char *i;
	for(i=str; i < str+len;i++)
	{
		if(src > 0)
		{
			tmp = src % 10;
			*i = (unsigned char)tmp;
			src = src / 10;
		}
		else
		{
			*i = leadingzero ? 0 : 0x10;
		}
	}
	return;
}
*/

void IntToBCD(unsigned int len, unsigned char str[], unsigned int src, unsigned char leadingzero)
{
	unsigned int tmp;

	unsigned char *i;
	for(i=str; i < str+len;i++)
	{
		if(src > 0)
		{
			tmp = src % 10;
			*i = (unsigned char)tmp;
			src = src / 10;
		}
		else
		{
			*i = leadingzero ? 0 : 10;
		}
	}
	return;
}
