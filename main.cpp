#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <utility>
#include <limits>

#include "utils.h"
//#include "delaunay.h"
#include "jarvis.h"


/// IO Utils
std::ostream& operator<<(std::ostream& out, const SPoint& point)
{
    out << point.x << " " << point.y;
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<SPoint>& vec)
{
    out << vec.size() << "\n";
    for (const auto & elem : vec) {
        out << elem << "\n";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec)
{
    int i = 0;
    for (const auto & elem : vec) {
        out << i++ << " " << elem << "\n";
    }
    return out;
}


std::istream& operator>>(std::istream& in, SPoint& point)
{
    in >> point.x >> point.y;
    return in;
}

std::istream& operator>>(std::istream& in, vtype& points)
{
    size_t size;
    in >> size;
    points.resize(size);
    for (auto & point : points) {
        in >> point;
    }
    return in;
}


class Timer
{
public:
    Timer(const std::string & name) :
        m_name(name),
        m_tic(std::chrono::high_resolution_clock::now())
    {
        std::cerr << m_name << " launched" << std::endl;
    }

    ~Timer()
    {
        auto toc = std::chrono::high_resolution_clock::now();
        auto msec = std::chrono::duration_cast<std::chrono::microseconds>(toc - m_tic).count();

        std::cerr << m_name << " completed in " << msec << " microseconds" << std::endl;
    }

private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_tic;
};


// argparser

struct SArgs {
    SArgs(int argc, char ** argv):
        m_argc(argc),
        m_argv(argv),
        is_valid(true)
    {
        if (argc < 3) {
            this->is_valid = false;
        } else {
            this->ifilename = argv[1];
            this->ofilename = argv[2];

            for (int i = 3; i < argc; ++i) {
                if (strcmp(argv[i], "--verbose") == 0) {
                    this->verbose = true;
                } else {
                    this->is_valid = false;
                }
            }
        }
    }

    void print_help_message(std::ostream& out = std::cerr)
    {
        out << "Usage " << m_argv[0] << " infile ofile [OPTIONS]\n"
            << "OPTIONS:\n"
            << "\t--verbose\tenable verbose mode\n";
        out << std::endl;
    }


    int m_argc;
    char ** m_argv;

    std::string ifilename;
    std::string ofilename;

    bool verbose;

    bool is_valid;
};


// SOLVER

class ProblemSolver {
public:
    void solve(vtype points);

    const std::vector<int> get_depths() const { return depths; }
    int get_max_depth() const { return max_depth; }

protected:
    std::vector<int> depths;
    int max_depth;
};


class JarvisProblemSolver : public ProblemSolver {
public:
    void solve(const vtype& points)
    {
        depths.resize(points.size());

        max_depth = 0;
        std::vector<pointidxtype> observer_order;
        observer_order.reserve(points.size());
        for (pointidxtype tmp = points.begin(); tmp != points.end(); ++tmp) {
            observer_order.push_back(tmp);
        }

        std::vector<observe_iterator> hull_layers;
        observe_iterator begin = observer_order.begin();
        observe_iterator end = observer_order.end();

        while (begin != end) {
            hull_layers.push_back(begin);
            int hull_len = jarvis_cvxhull_find(points, begin, end);
            begin += hull_len;
        }
        max_depth = hull_layers.size()-1;
        hull_layers.push_back(end);
        

        for (unsigned int nlayer = 0; nlayer + 1 < hull_layers.size(); ++nlayer) {
            for (observe_iterator it = hull_layers[nlayer]; it != hull_layers[nlayer + 1]; ++it) {
                int idx = *it - points.begin();
                depths[idx] = nlayer;
            }
        }
    }

private:
};


// MAIN

int main(int argc, char ** argv)
{
    Timer t("TOTAL_RUN");

    SArgs args(argc, argv);
    if (!args.is_valid) {
        args.print_help_message();
        return 1;
    }

    vtype points;
    {
        Timer t("read_points");
        std::ifstream(args.ifilename) >> points;
    }

    JarvisProblemSolver solver;
    {
        Timer t("solving_the_problem");
        solver.solve(points);
    }

    {
        Timer t("writing_answers");

        std::ofstream(args.ofilename)
            << args.ifilename << "\n"
            << "M(S): " << solver.get_max_depth() << "\n"
            << solver.get_depths();
    }

    return 0;
}

