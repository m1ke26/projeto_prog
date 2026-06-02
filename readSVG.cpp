#include <sstream>
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void apply_transform(XMLElement* child, SVGElement* elem){

        const char* t = child->Attribute("transform");
        if (t == nullptr) return;
        string transform = t;

        Point origin = {0, 0};
        const char* o = child->Attribute("transform-origin");
        if (o != nullptr) {
            stringstream ss(o);
            ss >> origin.x >> origin.y;
        }

        if (transform.find("translate") != string::npos) {
            for (char& c : transform) {
                if (c == '(' || c == ')') c = ' ';
            }
                stringstream ss(transform);
            string palavra;
            int x, y;
            ss >> palavra >> x >> y;
            elem->translate({x, y});
        }
        else if (transform.find("rotate") != string::npos) {
            for (char& c : transform) {
                if (c == '(' || c == ')') c = ' ';
            }
            stringstream ss(transform);
            string palavra;
            int angulo;
            ss >> palavra >> angulo;
            elem->rotate(origin, angulo);
        }
        else if (transform.find("scale") != string::npos) {
            for (char& c : transform) {
                if (c == '(' || c == ')') c = ' ';
            }
            stringstream ss(transform);
            string palavra;
            int fator;
            ss >> palavra >> fator;
            elem->scale(origin, fator);
        }
    }

    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");

        // TODO complete code -->
        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()){
            if(string(child->Name()) == "circle"){
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int r = child->IntAttribute("r");
                string fill = child->Attribute("fill");
                Color cor = parse_color(fill);
                Point center = {cx, cy};
                SVGElement* e = new Circle(cor, center, r);
                apply_transform(child, e);
                svg_elements.push_back(e);
            }

            else if(string(child->Name()) == "ellipse"){
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int rx = child->IntAttribute("rx");
                int ry = child->IntAttribute("ry");
                string fill = child->Attribute("fill");
                Color cor = parse_color(fill);
                Point center = {cx, cy};
                Point radius = {rx, ry};
                SVGElement* e = new Ellipse(cor, center, radius);
                apply_transform(child, e);
                svg_elements.push_back(e);
            }

            else if(string(child->Name()) == "polyline"){
                string points = child->Attribute("points");
                vector<Point> pts;
                stringstream ss(points);

                string stroke = child->Attribute("stroke");
                Color cor = parse_color(stroke);

                string par;
                while (ss >> par) {
                    stringstream par_ss(par);
                    string x_str, y_str;
                    getline(par_ss, x_str, ',');
                    getline(par_ss, y_str, ',');
                    int x = stoi(x_str);
                    int y = stoi(y_str);
                    pts.push_back({x, y});
                }
                SVGElement* e = new Polyline(cor, pts);
                apply_transform(child, e);
                svg_elements.push_back(e);
            }

            else if(string(child->Name()) == "rect"){
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                string fill = child->Attribute("fill");
                Color cor = parse_color(fill);
                SVGElement* e = new Rect(cor, width, height, x, y);
                apply_transform(child, e);
                svg_elements.push_back(e);
            }

            else if(string(child->Name()) == "line"){
                int x1 = child->IntAttribute("x1");
                int y1 = child->IntAttribute("y1");
                int x2 = child->IntAttribute("x2");
                int y2 = child->IntAttribute("y2");
                Point p1 = {x1, y1};
                Point p2 = {x2,y2};
                string stroke = child->Attribute("stroke");
                Color cor = parse_color(stroke);
                SVGElement* e = new Line(cor, p1, p2);
                apply_transform(child, e);
                svg_elements.push_back(e);
            }

            else if(string(child->Name()) == "polygon"){
                string fill = child->Attribute("fill");
                Color cor = parse_color(fill);
                string points = child->Attribute("points");
                vector<Point> pts;
                stringstream ss(points);


                string par;
                while (ss >> par) {
                    stringstream par_ss(par);
                    string x_str, y_str;
                    getline(par_ss, x_str, ',');
                    getline(par_ss, y_str, ',');
                    int x = stoi(x_str);
                    int y = stoi(y_str);
                    pts.push_back({x, y});
                }
                SVGElement* e = new Polygon(cor, pts);
                apply_transform(child, e);
                svg_elements.push_back(e);
            }
        }
    }
}