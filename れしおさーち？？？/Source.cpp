#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <limits>
#include <algorithm>
#include <tuple>

typedef std::vector<std::uint64_t> DType;


DType MakeVector(const std::size_t N,const std::uint32_t RS=0) {

	std::minstd_rand mr(RS);
	//std::uniform_int_distribution<DType::value_type> UI(0, std::numeric_limits<DType::value_type>::max());

	std::uniform_int_distribution<std::uint16_t> UI(0, std::numeric_limits<std::uint16_t>::max());


	DType R;

	for (std::size_t i = 0; i < N;i++) {
		R.push_back(UI(mr));
	}
	std::stable_sort(R.begin(), R.end());
	return R;
}

std::tuple<bool,std::size_t> BinarySearch(const DType& D, const DType::value_type& Value) {

	std::int64_t P = 0;
	std::int64_t F= 0;
	std::int64_t L= (D.size());
	std::int64_t OP = -1;

	while (L>F) {

		if (D[P] == Value)break;
		if (OP == P)break;
		OP = P;
		P = (F + L) / 2;
		if (D[P] < Value) {
			F = (P+F+2)/2;
		}
		else {			
			L = (P+L-2)/2;
		}

	}

	return { D[P]==Value,P };
}
/**  /
std::size_t BinarySearch_Custom(const DType& D, const DType::value_type& Value,std::size_t F,std::size_t L) {

	std::int64_t P = 0;
	std::int64_t OP = -1;

	while (L>F) {

		if (D[P] == Value)break;
		if (OP == P)break;
		OP = P;
		P = (F + L) / 2;
		if (D[P] < Value) {
			F = (P+F+2)/2;
		}
		else {			
			L = (P+L-2)/2;
		}

	}

	return P;
}
std::size_t BinarySearch_Low(const DType& D, const DType::value_type& Value,std::size_t Div) {

	//std::int64_t P = 0;
	//std::int64_t F= 0;
	//std::int64_t L= (D.size()/Div);
	//std::int64_t OP = -1;
	double P = 0;
	double F= 0;
	double L= ((D.size()-1)/(double)Div);
	double OP = -1;
	while (L>F) {

		if (D[P*Div] == Value)break;
		if (OP == P)break;
		OP = P;
		P = (F + L) / 2;
		
		if (D[P*Div] < Value) {
			F = (P+F+2)/2;
		}
		else {			
			L = (P+L-2)/2;
		}

	}

	return P;
}

std::size_t RatioSearch(const DType& D, const DType::value_type& Value,const std::size_t& Div = 256) {

	auto Low = [](const DType& D, const DType::value_type& Value, std::size_t Div) {
		//std::int64_t P = 0;
		//std::int64_t F= 0;
		//std::int64_t L= (D.size()/Div);
		//std::int64_t OP = -1;
		double P = 0;
		double F= 0;
		double L= ((D.size()-1)/(double)Div);
		double OP = -1;
		while (L > F|| OP!=P) {

			if (D[P * Div] == Value)break;
			if (OP == P)break;
			OP = P;
			P = (F + L) / 2;

			if (D[P * Div] < Value) {
				F = (P + F + 1) / 2;
			}
			else {
				L = (P + L - 1) / 2;
			}

		}

		return P;
	};

	auto Custom = [](const DType& D, const DType::value_type& Value, std::size_t F, std::size_t L) {

		std::int64_t P = 0;
		std::int64_t OP = -1;

		while (L > F) {

			if (D[P] == Value)break;
			if (OP == P)break;
			OP = P;
			P = (F + L) / 2;
			if (D[P] < Value) {
				F = (P + F + 2) / 2;
			}
			else {
				L = (P + L - 2) / 2;
			}

		}

		return P;
	};

	std::size_t P = Low(D, Value, Div);
	std::size_t L = D.size() / Div;
	return Custom(D, Value, P ? (P - 1)*Div : 0, std::min((P+1)*L,D.size()) );


}
/**/
/** /
int main() {

	std::size_t Nu = 32;

	auto D = MakeVector(Nu);

	for (std::size_t i = 0; i < D.size(); i++) {
		DType::value_type Value = D[i]*2;
		std::size_t N =  RatioSearch(D,Value);
		std::cout << N << ',' << D[N] << ',' << Value << std::endl;
	}
	return 0;
}
/**/
int main() {

	std::size_t N = 32;

	auto D = MakeVector(N);
	auto i = 15;
	for (std::size_t i = 0; i < D.size(); i++) {
		DType::value_type V = D[i]*2;
		auto [b, N] = BinarySearch(D, V);
		std::cout << N << ',' << D[N] << (b?" == ":" != ")<< V << std::endl;
	}
	return 0;
}
/**/