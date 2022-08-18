#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

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
	Mean() : m_mean{.0}, m_sum{.0}, m_count{0.} {
	}

	void update(double next) override {
		m_sum += next;
		++m_count;
		m_mean = m_sum / m_count;
	}
				
	double eval()  const override {
		return m_mean;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_mean;
	double m_sum;
	double m_count;
};

class Std : public IStatistics {
public:
	Std() : m_std{.0}, m_mean{m_mean}, m_sum{.0}, m_count{0.} {
	}
	
	void update(double next) override {
		m_range.push_back(next);
	}
	
	double calc(std::vector<double> range) {
		for(double i : range) {
			m_sum += i;
		}
		
		m_mean = m_sum / range.size();

		for(double i : m_range) {
			m_sumn += (i - m_mean) * (i - m_mean);
		}

		m_std = sqrt(m_sumn / (range.size() - 1));
		return m_std;
	}
	
	double eval() const override {
		return m_std;
	}

	const char * name() const override {
		return "std";
	}

private:
	double m_std;
	double m_mean;
	double m_sum;
	double m_sumn;
	double m_count;
	std::vector<double> m_range;
};

class Pct90 : public IStatistics {
public:
	Pct90() : m_pct90{.0}, m_count{0}, m_range{} {}

	void update (double next) override {
		m_range.push_back(next);
		m_count = 0.9 * m_range.size();
		m_pct90 = m_range[m_count];
	}

	double eval() const override {
		return m_pct90;
	}

	const char * name() const override {
		return "pct90";
	}

private:
	double m_pct90;
	double m_count;
	std::vector<double> m_range;
};

class Pct95 : public IStatistics {
public:
	Pct95() : m_pct95{.0}, m_count{0}, m_range{} {}

	void update (double next) override {
		m_range.push_back(next);

		m_count = 0.95 * m_range.size();
		m_pct95 = m_range[m_count];
	}

	double eval() const override {
		return m_pct95;
	}

	const char * name() const override {
		return "pct95";
	}

private:
	double m_pct95;
	double m_count;
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