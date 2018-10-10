#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <cmath>

int random(int start, int end)
{
	std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end);
    return dist6(rng);
}

template <typename T> T nextPrime(T num)
{
	for (T i = 2; i*i <= num; ++i)
		if(num % i == 0)
			return nextPrime(++num);
	return num;
}

template <typename T> T totient(T p, T q)
{
	return (p-1)*(q-1);
}

template <typename T> T gcd(T a, T b)
{
	while(b != 0)
	{
		T tmp = a % b;
        a = b;
        b = tmp;
	}

	return a;
}

template <typename T> T publicKey(T t)
{
	for(T i = 2 ; i < t; ++i)
	{
		if(gcd(i, t) == 1)
			return i;
	}

	return -1;
}

template <typename T> T privateKey(T e, T t)
{
	T k = 1;

	while(true)
	{
		k += t;

		if(k % e == 0)
			return k / e;
	}
}

template <typename T> inline T modPow(T base, T exp, T mod)
{
	T result = 1;
	base %=mod;

	while(exp > 0)
	{
		if(exp & 1)
			result = (result * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}

	return result;
}

template <typename T> T encrypt(T i , T e, T n)
{
	return modPow<T>(i, e, n);
}

template <typename T> T decrypt(T i, T d, T n)
{
	return modPow<T>(i, d, n);
}

int main(int argc, char const *argv[])
{
	std::string msg;

	std::cout << "Enter Message to be encrypted : " << std::endl;

	// std::cin.ignore();

	std::getline(std::cin, msg);

	std::cout <<  "The message is : " << msg << std::endl;

	long long encryptedText[100], decryptedText[100];

	auto rand1 = random(10000 , 20000);
	auto rand2 = random(10000 , 20000);
	auto p = nextPrime<long long>(rand1);
	auto q = nextPrime<long long>(rand2);

	std::cout << "p : " << p << std::endl;
	std::cout << "q : " << q << std::endl;

	auto n = p * q;
	auto t = totient<long long>(p, q);

	std::cout << "n : " << n << std::endl;
	std::cout << "totient : " << t << std::endl;
	auto e = publicKey<long long>(t);

	std::cout << "e : " << e << std::endl;

	auto d = privateKey<long long>(e, t);

	std::cout << "d : " << d << std::endl;

	for (int i = 0; i < msg.length(); ++i)
	{
		encryptedText[i] = encrypt<long long>(msg[i], e, n);
	}

	std::cout << "The encrypted message is : " << std::endl;
	for (int i = 0; i < msg.length(); ++i)
	{
		std::cout << encryptedText[i] ;
	}

	std::cout << std::endl;

	for (int i = 0; i < msg.length(); ++i)
	{
		decryptedText[i] = decrypt<long long>(encryptedText[i], d, n);
	}

	std::cout << "The decrypted message is : " << std::endl;
	for (int i = 0; i < msg.length(); ++i)
	{
		std::cout <<  (char) decryptedText[i] ;
	}

	std::cout << std::endl;

	return 0;
}