# Wikipedia Scraper

A simple C++ project for scraping Wikipedia pages to extract specific elements, such as the page title. This project uses `libcurl` for HTTP requests and `gumbo-parser` for HTML parsing.

## Features

- Fetches HTML content from Wikipedia pages.
- Parses HTML to extract specific elements (e.g., page titles).
- Modular and extensible design for future enhancements.
- Error handling for common issues (e.g., network failures, parsing errors).

## Requirements

Before building the project, ensure you have the following installed:

- **C++ Compiler**: g++ or any C++17-compatible compiler.
- **Libraries**:
  - [libcurl](https://curl.se/libcurl/) for HTTP requests.
  - [gumbo-parser](https://github.com/google/gumbo-parser) for HTML parsing.

### Installation on Linux
```bash
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install gumbo-parser-dev
```

### Installation on Windows
- Download [libcurl](https://curl.se/download.html) and [gumbo-parser](https://github.com/google/gumbo-parser).
- Link the downloaded libraries with your C++ project.

## Build Instructions

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/wikipedia-scraper.git
   cd wikipedia-scraper
   ```

2. Compile the code:
   ```bash
   g++ -o wikipedia_scraper wikipedia_scraper.cpp -lcurl -lgumbo
   ```

3. Run the program:
   ```bash
   ./wikipedia_scraper
   ```

## Usage

The scraper fetches the title of a specified Wikipedia page. By default, the program uses the URL for the "Web scraping" Wikipedia page:  
`https://en.wikipedia.org/wiki/Web_scraping`.

Modify the `url` variable in the `main()` function to target a different Wikipedia page.

### Example Output
```plaintext
Fetching HTML from: https://en.wikipedia.org/wiki/Web_scraping
Parsing HTML to extract title...
Page Title: Web scraping
```

## Code Structure

- **`HttpClient`**: Handles HTTP requests using libcurl.
- **`searchForText`**: Recursively searches for specific HTML elements.
- **`extractTitle`**: Extracts the Wikipedia page title from the HTML.

## Future Improvements

- Extract additional elements like paragraphs, lists, or tables.
- Support for multilingual Wikipedia pages.
- Add unit tests for better code coverage.
- Dockerize the application for easier deployment.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributions

Contributions are welcome! Feel free to submit issues or pull requests to improve the project.
