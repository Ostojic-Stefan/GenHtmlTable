#include <iostream>

#include "Rectangle.hpp"
#include "utils.hpp"
#include "structureGeneration.hpp"
#include "parser.hpp"
#include "tableGeneration.hpp"

void outputHtml(const std::string &contents, const std::string &templateFilename,
                const std::string &outputFilename, const std::string &region)
{
    std::string htmlTemplate = utils::readAllFileContents(templateFilename);
    size_t pos = htmlTemplate.find(region);

    if (pos != std::string::npos)
        htmlTemplate.replace(pos, region.size(), contents);

    utils::dumpToFile(outputFilename, htmlTemplate);
}

int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     std::cerr << "Usage: gentable <path_to_file>\n";
    //     exit(1);
    // }

    // std::filesystem::path filePath = argv[1];
    // if (!std::filesystem::exists(filePath))
    // {
    //     std::cerr << "Provided File does not exist\n";
    //     exit(1);
    // }

    // std::vector<Rectangle> rectangles = parseInput(argv[1]);

    const std::vector<Rectangle> rectangles = parseInput("Rectangles.txt");
    const auto &[width, height] = getTableDimensions(rectangles);
    const auto structure = genStructure(width, height, rectangles);
    const std::string result = genTable(structure);

    outputHtml(result, "template.html", "output.html", "{{#input}}");
    return 0;
}
