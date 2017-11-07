#include <bits/stdc++.h>
using namespace std;

#define pi 3.141592653589793238462643


class Complex{
	
	public :
		double a,b;
		Complex(double a_=0,double b_=0)
		{
			a = a_;
			b = b_;
		}
		
		Complex operator + (Complex c)
		{
			Complex temp;
			temp.a = a+c.a;
			temp.b = b+c.b;
			return temp;
		}
		Complex operator - (Complex c)
		{
			Complex temp;
			temp.a = a-c.a;
			temp.b = b-c.b;
			return temp;
		}
		Complex operator * (Complex c)
		{
			Complex temp;
			temp.a = (a*c.a - b*c.b);
			temp.b = (a*c.b + b*c.a);
			return temp;
		}
		friend ostream & operator << (ostream & out, const Complex & c);
};

ostream & operator << (ostream & out,const Complex & c)
{
	out << fixed << setprecision(2) << c.a;
	if(c.b>=0)out << "+";
	out << fixed << setprecision(2) << c.b << "i";
	return out;
	
}

vector<Complex> iterative_fft(vector<Complex> ar)
{
	int n = ar.size();
	vector<Complex> ans(n);
	
	for(int i=0;i<n;i++)
	{
		int j = i,k=0,ct = log2(n);
		while(ct--)
		{
			k = 2*k+(j%2);
			j/=2;
		}
		ans[k] = ar[i];
	}
	
	for(int i=1;i<=log2(n);i++)
	{
		int dif = 1<<i;
		for(int j=0;j<n;j+=dif)
		{
			double theta = (2*pi)/dif;
			Complex w(1,0),wn(cos(theta),sin(theta));
			for(int k=j;k<j+(dif/2);k++)
			{
				Complex u = ans[k];
				Complex t = w*ans[k+(dif/2)];
				ans[k]=u+t;
				ans[k+(dif/2)]=u-t;
				w=w*wn;
			}
		}
	}
	return ans;
}

int main ()
{
	
	cout << "Enter degree of polynomial " << endl;
	int n;
	cin >> n;
	vector<Complex> ar;
	ar.clear();
	cout << "Enter coefficients " << endl;
	for(int i=0;i<n;i++)
	{
		Complex tp;
		cin >> tp.a;
		tp.b = 0;
		ar.push_back(tp);
	}
	
	vector<Complex> ans;
	ans.clear();
	
	ans = iterative_fft(ar);
	for(int i=0;i<n;i++)cout << ans[i] << " ";
	cout << endl;
	
	return 0;
}
