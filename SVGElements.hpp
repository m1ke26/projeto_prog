//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <bitset>
#include <deque>
#include <forward_list>

namespace svg
{
    class SVGElement
    {

    public:
        int vElement = 0;
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point center;
        Point radius;
    };
    /*-----------------------------------------------------------*/
    class Circle : public Ellipse
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
    };
    /*-----------------------------------------------------------*/
    class Polyline : public SVGElement
    {
    public:
        Polyline(const Color &stroke, std::vector<Point> &points);
        void draw(PNGImage &img) const override;

    private:
        Color stroke;
        std::vector<Point> points;
    };
    /*-----------------------------------------------------------*/
    class Line : public Polyline
    {
    public:
        Line(const Color &stroke, Point &point1, Point &point2);
    };
    /*-----------------------------------------------------------*/
    class Polygon : public SVGElement
    {
    public:
        Polygon(const Color &fill, std::vector<Point> &points);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        std::vector<Point> points;
    };
    /*-----------------------------------------------------------*/
    class Rect : public Polygon /*rect = rectangulo*/
    {
    public:
        Rect(const Color &fill, int width, int height, int x, int y);
    };
    /*-----------------------------------------------------------*/
    class Group : public SVGElement
    {
    public:
        Group(std::vector<SVGElement *> &element);
        void draw(PNGImage &img) const override;

    private:
        std::vector<SVGElement *> element;
    };
}
#endif
