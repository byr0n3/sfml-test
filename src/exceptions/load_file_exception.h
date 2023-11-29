#include <exception>
#include <string>

namespace byrone {
	class load_file_exception : std::exception {
	public:
		explicit load_file_exception(const char *path) : path(path) {
		}

		[[nodiscard]] const char *what() const noexcept override {
			return std::string("Couldn't load and/or parse file at path: ").append(this->path).c_str();
		}

	private:
		const char *path;
	};
}
