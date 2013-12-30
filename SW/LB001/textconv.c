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

char * ByteToStr(char src, char str[])
{
// 	unsigned char str[4];
	str += 3;
	*str = 0;
	do
	{
		str--;
		*str = (src % 10) + 0x30;
		src /= 10;
	}
	while(src);
	return str;
}
