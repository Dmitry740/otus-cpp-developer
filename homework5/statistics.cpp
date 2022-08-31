#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <numeric>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if(next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	Mean() : m_range{} {
	}

	void update(double next) override {
		m_range.push_back(next);
	}
				
	double eval()  const override {
		const auto sum = std::accumulate(m_range.begin(), m_range.end(), .0);
		// double sum = 0;
		// for(auto i : m_range) {
		// 	sum += i;
		// }

		return (sum / m_range.size());
	}

	const char * name() const override {
		return "mean";
	}

private:
	std::vector<double> m_range;
};

class Std : public IStatistics {
public:
	Std() : m_range{} {
	}
	
	void update(double next) override {
		m_range.push_back(next);
	}

	double eval() const override {
		const auto sum = std::accumulate(m_range.begin(), m_range.end(), .0);

		// double sum = 0;
		// for(const auto i : m_range) {
		// 	sum += i;
		// }
			
		const auto mean = sum / m_range.size();

		std::vector<double> newrange;
		
		newrange.reserve(m_range.size());

		for(double i : m_range) {
			const auto sumn = (i - mean) * (i - mean);
			newrange.push_back(sumn);
		}

		const auto sumstd = std::accumulate(newrange.begin(), newrange.end(), .0);

		// double sumstd = 0;
		// for(const auto i : m_range) {
		// 	sumstd += i;
		// }
			
		const auto newmean = sumstd / newrange.size();

		return sqrt(newmean);
		}

	const char * name() const override {
		return "std";
	}

private:
	std::vector<double> m_range;
};

class Pct90 : public IStatistics {
public:
	Pct90() : m_range{} {}

	void update (double next) override {
		m_range.push_back(next);
	}

	double eval() const override {
		const auto rangecount = static_cast<size_t>(0.9 * m_range.size());
	
		return m_range[rangecount];
	}

	const char * name() const override {
		return "pct90";
	}

private:
	std::vector<double> m_range;
};

class Pct95 : public IStatistics {
public:
	Pct95() : m_range{} {}

	void update (double next) override {
		m_range.push_back(next);
	}

	double eval() const override {
		const auto rangecount = static_cast<size_t>(0.95 * m_range.size());
	
		return m_range[rangecount];
	}

	const char * name() const override {
		return "pct95";
	}

private:
	std::vector<double> m_range;
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct90{};
	statistics[5] = new Pct95{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}
	
	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}
	
	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}