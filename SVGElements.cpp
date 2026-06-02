#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill, const Point &center, const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    /*-----------------------------------------------------------*/
    Circle::Circle(const Color &fill, const Point &center, const int radius)
        : Ellipse(fill, center, {radius, radius})
    {
    }
    /*-----------------------------------------------------------*/
    Polyline::Polyline(const Color &stroke, const std::vector<Point> &points)
        : stroke(stroke), points(points)
    {
    }
    void Polyline::draw(PNGImage &img) const
    {
        for (size_t i = 0; i + 1 < points.size(); i++)
        {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }
    /*-----------------------------------------------------------*/
    Line::Line(const Color &stroke, const Point &point1, const Point &point2)
        : Polyline(stroke, {point1, point2})
    {
    }
    /*-----------------------------------------------------------*/
    Polygon::Polygon(const Color &fill, const std::vector<Point> &points)
        : fill(fill), points(points)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }
    /*-----------------------------------------------------------*/
    Rect::Rect(const Color &fill, int width, int height, int x, int y)
        : Polygon(fill, {{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}})
    {
    }
    /*-----------------------------------------------------------*/
    Group::Group(const std::vector<SVGElement *> &element)
        : element(element)
    {
    }
    void Group::draw(PNGImage &img) const
    {
        for (size_t i = 0; i < element.size(); i++)
        {
            element[i]->draw(img);
        }
    };
}
