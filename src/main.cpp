#include <iostream>
#include <ranges>
#include <print>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <regex>
#include <optional>
#include <tuple>

struct Pos
{
    int x;
    int y;
};

Pos operator+(Pos a, Pos b)
{
    return Pos{a.x + b.x, a.y + b.y};
}

bool operator==(Pos const &l, Pos const &r)
{
    return std::tie(l.x, l.y) == std::tie(r.x, r.y);
}

std::ostream &operator<<(std::ostream &os, Pos const &pos)
{
    return os << '(' << pos.x << ',' << pos.y << ')';
}

using Path = std::vector<Pos>;

bool Collides(Pos const &spaceship, Pos const &asteroid)
{

    return (std::abs(asteroid.x - spaceship.x) < 3) && (std::abs(asteroid.y - spaceship.y) < 3);
}

Path normalize(Path const &path, Pos const &dst)
{
    if (dst.x < 0)
    {
        std::for_each(std::begin(path), std::end(path), [](auto p)
                      { return Pos{-p.x, p.y}; });
    }

    if (dst.y < 0)
    {
        std::for_each(std::begin(path), std::end(path), [](auto p)
                      { return Pos{p.x, -p.y}; });
    }

    return path;
}

std::optional<Path> get_path(Path path, Pos curr_pos, Pos asteroid, Pos dst, int max_time)
{
    std::cout << curr_pos << std::endl;

    if (path.size() > max_time)
    {
        std::cout << "timeout" << std::endl;
        return std::nullopt;
    }

    if (curr_pos.x < 0 || curr_pos.y < 0)
    {
        std::cout << "negative" << std::endl;
        return std::nullopt;
    }

    if (curr_pos.x > dst.x + 10 || curr_pos.y > dst.y + 10)
    {
        std::cout << "outside" << std::endl;
        return std::nullopt;
    }

    if (Collides(curr_pos, asteroid))
    {
        std::cout << "collision" << std::endl;
        return std::nullopt;
    }

    if (curr_pos == dst)
    {
        std::cout << "dst" << std::endl;
        return path;
    }

    std::cout << "continue" << std::endl;
    path.push_back(curr_pos);

    std::cout << "going left" << std::endl;
    auto left_path = get_path(path, curr_pos + Pos{-1, 0}, asteroid, dst, max_time);
    std::cout << "going right" << std::endl;
    auto right_path = get_path(path, curr_pos + Pos{1, 0}, asteroid, dst, max_time);
    std::cout << "going up" << std::endl;
    auto up_path = get_path(path, curr_pos + Pos{0, 1}, asteroid, dst, max_time);
    std::cout << "going down" << std::endl;
    auto down_path = get_path(path, curr_pos + Pos{0, -1}, asteroid, dst, max_time);

    if (left_path)
        return left_path;
    if (right_path)
        return right_path;
    if (up_path)
        return up_path;
    if (down_path)
        return down_path;

    return std::nullopt;
}

void print_path_x(const Path &path)
{
    for (auto const &pos : path)
    {
        std::cout << pos.x << ' ';
    }
    std::cout << std::endl;
    ;
}

void print_path_y(const Path &path)
{
    for (auto const &pos : path)
    {
        std::cout << pos.y << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::ifstream in{"/Users/elvisdukaj/Projects/content/assets/level5_0_example.in"};
    std::string str;
    std::getline(in, str);

    while (std::getline(in, str))
    {
        std::string asteroid_str;
        std::getline(in, asteroid_str);

        std::replace_if(begin(str), end(str), [](char c)
                        { return c == ','; }, ' ');
        std::replace_if(begin(asteroid_str), end(asteroid_str), [](char c)
                        { return c == ','; }, ' ');
        int x_dst, y_dst, max_time, asteroid_x, asteroid_y;

        std::stringstream dstss{str};
        dstss >> x_dst >> y_dst >> max_time;

        std::stringstream asteroidss{asteroid_str};
        asteroidss >> asteroid_x >> asteroid_y >> max_time >> asteroid_x >> asteroid_y;

        auto dst = Pos{x_dst, y_dst};
        auto asteroid = Pos{asteroid_x, asteroid_y};

        std::cout << dst << ' ' << asteroid << std::endl;

        std::cout << "max_time: " << max_time;

        Path path = get_path(Path{}, Pos{0, 0}, asteroid, Pos{std::abs(dst.x), std::abs(dst.y)}, max_time).value_or(Path{});

        print_path_x(path);
        print_path_y(path);
    }
}
