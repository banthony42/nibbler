#include "Graphics.hpp"

std::vector<eEvent> AGraphics::_eventList;

Graphics::Graphics() {

}

Graphics::Graphics(Graphics const &copy) {
    *this = copy;
}

Graphics::~Graphics() {

}

Graphics &Graphics::operator=(Graphics const &copy) {
    if (this != &copy) {
        // copy
    }
    return *this;
}

 int Graphics::loopUpdate() {
//     std::cout << "test" << std::endl;
//     this->getEvent(); // useless
     return !glfwWindowShouldClose(this->_window) && !this->_windowTerminated;
}

void Graphics::display() {

}

void Graphics::clear() {

}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path, int key) {

}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {

}

void Graphics::closeWindow() { // TODO soit on garde closeWindow ET cleanUp soit on garde que cleanUp (->UML)
//	std::cout << "Should close and terminate" << std::endl;
    this->cleanUp();
}

void Graphics::cleanUp() {
    if (!this->_windowTerminated) {
        std::cout << "terminate" << std::endl;
        glfwTerminate();
        vkDestroyInstance(this->_instance, nullptr);
        this->_windowTerminated = true;
    }
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	std::cout << "key callback : " << key << std::endl;

	AGraphics::clearEvent();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		AGraphics::addEvent(ECHAP);
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		AGraphics::addEvent(UP);
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		AGraphics::addEvent(DOWN);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		AGraphics::addEvent(LEFT);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		AGraphics::addEvent(RIGHT);
	else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		AGraphics::addEvent(ENTER);
}

std::vector<eEvent> &Graphics::getEvent() {
	glfwPollEvents();
	return Graphics::_eventList;
}

unsigned char Graphics::getChar() {
	return 0;
}

int Graphics::init(int windowWidth, int windowHeight) {
    initWindow(windowWidth, windowHeight);
    glfwSetKeyCallback(_window, key_callback);
    this->_windowTerminated = false;
    try {
        createInstance();
        pickGraphicDevice();
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return (0);
    }
	return (1);
}

void Graphics::initWindow(int windowWidth, int windowHeight) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);	// Desactive la creation de context, Vulkan dispose de son propre API
    this->_window = glfwCreateWindow(windowWidth, windowHeight, "Vulkan", nullptr, nullptr);
}

void checkExtensions(std::vector<const char*> GLFWextensions){
	//check the extensions available
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout<<"\tNeeded Extensions: "<<std::endl;
	for (int i = 0; i<GLFWextensions.size(); i++) {
		std::cout << "\t\t-" << GLFWextensions[i] << std::endl;
	}
	std::cout << "\tAvailable extensions:" << std::endl;
	for (const auto& extension : extensions) {
		std::cout << "\t\t-" << extension.extensionName << std::endl;
	}
	std::cout<<"\tChecking if all extensions are supported:\n";
	int allPass = 1;
	for (int i = 0; i<GLFWextensions.size(); i++) {
		int present = 0;
		for (const auto& extension : extensions) {
			std::string extensionName = extension.extensionName;
			std::string GLFWextensionName = GLFWextensions[i];
			if (extensionName == GLFWextensionName) {
				present = 1;
				break;
			}
		}
		if (present) {
			std::cout << "\t\t-" << GLFWextensions[i] << " is supported"<<std::endl;
		}
		else{
			std::cout << "\t\t-" << GLFWextensions[i] << " is not supported"<<std::endl;
			allPass = 0;
		}
	}
	if (allPass) {
		std::cout<<"\t-All required extensions are supported\n";
	}
	else{
		throw std::runtime_error("EXTENSION FAILURE: all the extensions needed are not supported\n");
	}
}

std::vector<const char*> getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	return extensions;
}

void Graphics::createInstance() {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Application Name";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

	VkResult result;
    if ((result = vkCreateInstance(&createInfo, nullptr, &this->_instance)) != VK_SUCCESS) {
        throw std::runtime_error(std::string("failed to create instance! error :") + std::to_string(result));
    }
	std::cout << result << std::endl;
}

void Graphics::pickGraphicDevice() {
    this->_physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(this->_instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(this->_instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            this->_physicalDevice = device;
            break;
        }
    }

    if (this->_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool Graphics::isDeviceSuitable(VkPhysicalDevice const &device) {
    VkPhysicalDeviceProperties deviceProperties = {};
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}

Graphics::QueueFamilyIndices Graphics::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices = -1;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices = i;
		}
		if (this->isQueueFamilyIndicesComplete(indices)) {
			break;
		}
		i++;
	}
	return indices;
}

void Graphics::createCommandPool() {

}

bool Graphics::isQueueFamilyIndicesComplete(Graphics::QueueFamilyIndices queueFamilyIndices) {
	return queueFamilyIndices >= 0;
}


/********* EXTERN "C" DEFINITION *********/

Graphics    *createGraphics() {
    return new Graphics();
}

















