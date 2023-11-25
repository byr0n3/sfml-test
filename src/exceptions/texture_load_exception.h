#include <exception>
#include <string>

namespace byrone {
	class texture_load_exception : std::exception {
	public:
		explicit texture_load_exception(const char *texturePath) : texturePath(texturePath) {
		}

		[[nodiscard]] const char *what() const noexcept override {
			return std::string("Couldn't load texture at path: ").append(this->texturePath).c_str();
		}

	private:
		const char *texturePath;
	};
}