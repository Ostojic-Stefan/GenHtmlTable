#include <iostream>
#include <filesystem>

#include "./headers/utils.hpp"
#include "./headers/structureGeneration.hpp"
#include "./headers/parser.hpp"
#include "./headers/tableGeneration.hpp"

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
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_file>\n";
        exit(1);
    }

    std::filesystem::path filePath = argv[1];
    if (!std::filesystem::exists(filePath))
    {
        std::cerr << "Provided File does not exist\n";
        return 1;
    }

    std::vector<Rectangle> rectangles = parseInput(argv[1]);

    const auto &[width, height] = getTableDimensions(rectangles);
    const auto structure = genStructure(width, height, rectangles);
    const std::string result = genTable(structure);

    outputHtml(result, "./assets/template.html", "output.html", "{{#input}}");
    return 0;
}
