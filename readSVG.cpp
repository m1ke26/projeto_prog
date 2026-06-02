#include <sstream>
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
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
                svg_elements.push_back(new Circle(cor, center, r));
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
                svg_elements.push_back(new Ellipse(cor, center, radius));
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
                svg_elements.push_back(new Polyline(cor, pts));
            }

            else if(string(child->Name()) == "rect"){
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                string fill = child->Attribute("fill");
                Color cor = parse_color(fill);
                svg_elements.push_back(new Rect(cor, width, height, x, y));
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
                svg_elements.push_back(new Line(cor, p1, p2));
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
                svg_elements.push_back(new Polygon(cor, pts));
            }
        }
    }
}