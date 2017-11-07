#include <bits/stdc++.h>
using namespace std;
#define pi 3.141592653589793238462643

class Complex{
	public:
	double a,b;
	Complex(double a_=0,double b_=0)
	{
		a=a_;
		b=b_;
	}
	
	Complex operator + (Complex c)
	{
		Complex temp;
		temp.a  = a+c.a;
		temp.b = b+c.b;
		return temp;
	}
	Complex operator - (Complex c)
	{
		Complex temp;
		temp.a  = a-c.a;
		temp.b = b-c.b;
		return temp;
	}
	Complex operator * (Complex c)
	{
		Complex temp;
		temp.a = (a*c.a-b*c.b);
		temp.b = (a*c.b+b*c.a);
		return temp;
	}
	friend ostream & operator << (ostream & out, const Complex & c);
};

ostream & operator  << (ostream & out,const Complex & c)
{
	if(c.b==0)out<< fixed<< setprecision(2) << c.a;
	else
	{
		out<< fixed << setprecision(2) << c.a << "";
		if(c.b>0)cout << "+";
		out << fixed << setprecision(2) << c.b << "i";
	}
	return out;
}

vector<Complex> recursive_fft(vector<Complex> ar)
{
	int n = ar.size();
	if(n==1)
	{
		vector<Complex> tp;
		tp.clear();
		tp.push_back(ar[0]);
		return tp;
	}
	vector<Complex> ar0,ar1,y0,y1;
	y0.clear();y1.clear();
	for(int i=0;i<n;i++)
	{
		if(i&1)ar1.push_back(ar[i]);
		else ar0.push_back(ar[i]);
	}
	y0 = recursive_fft(ar0);
	y1 = recursive_fft(ar1);
	
	double theta = (2*pi)/n;
	Complex w(1,0),wn(cos(theta),sin(theta));	
	vector<Complex> ans(2*n);
	int mid = (n/2);
	for(int i=0;i<n/2;i++)
	{
		ans[i] = y0[i]+w*y1[i];
		ans[i+mid] = y0[i]-w*y1[i];
		w = w*wn;
	}
	
	return ans;
}

int main()
{	
	cout << "Enter degree of polynomial" << endl;
	int n;
	cin >> n;
	
	vector<Complex> ar;
	vector<Complex> ans(n);
	ans.clear();
	ar.clear();
	
	for(int i=0;i<n;i++)
	{
		Complex tp;
		cin >> tp.a;
		tp.b = 0;
		ar.push_back(tp);
		ans[i] = tp;
	}
	
	ans = recursive_fft(ar);
	
	cout << "arr = " << endl;
	
	for(int i=0;i<n;i++)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
	
	cout << "ans = " << endl;
	
	for(int i=0;i<n;i++)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
}
