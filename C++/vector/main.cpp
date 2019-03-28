/**
 *	@file
 *	@brief some example of Vector
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#include "vector.cpp"

int main(void)
	{
		int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		Vector<int> a(10, arr);
		Vector<int> b(10, 2);
		Vector<int> c(30);

		Vector<int>* d = NEW Vector<int>;

		c = a * 5;

		a[3] = 5;

		cout << a << endl;

		DELETE(d);
	}
