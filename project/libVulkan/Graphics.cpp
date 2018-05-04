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
//	 std::cout << "test" << std::endl;
//	 this->getEvent(); // useless
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
		vkDestroyDevice(this->_device, nullptr);
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
		createLogicalDevice();
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		return (0);
	}
	return (1);
}

void Graphics::initWindow(int windowWidth, int windowHeight) {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API,
				   GLFW_NO_API);    // Desactive la creation de context, Vulkan dispose de son propre API
	this->_window = glfwCreateWindow(windowWidth, windowHeight, "Vulkan", nullptr, nullptr);
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
	const char **glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	VkResult result;
	if ((result = vkCreateInstance(&createInfo, nullptr, &this->_instance)) != VK_SUCCESS) {
		throw std::runtime_error(std::string("failed to create instance! error :") + std::to_string(result));
	}
	std::cout << "MESSAGE : success create instance" << std::endl;
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
	for (const auto &device : devices) {
		if (isDeviceSuitable(device)) {
			this->_physicalDevice = device;
			break;
		}
	}
	if (this->_physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
	std::cout << "MESSAGE : graphic card pick" << std::endl;
}

void Graphics::createLogicalDevice() {
	QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices;
	queueCreateInfo.queueCount = 1;
	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;
	VkPhysicalDeviceFeatures deviceFeatures = {};
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;

	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledLayerCount = 0;
	VkResult result;
	if ((result = vkCreateDevice(this->_physicalDevice, &createInfo, nullptr, &this->_device)) != VK_SUCCESS) {
		throw std::runtime_error(std::string("failed to create logical device! error :") + std::to_string(result));
	}
	vkGetDeviceQueue(this->_device, indices, 0, &this->_graphicsQueue);
	std::cout << "MESSAGE : logical device created" << std::endl;
}

bool Graphics::isDeviceSuitable(VkPhysicalDevice const &device) {
	VkPhysicalDeviceProperties deviceProperties = {};
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		   this->isQueueFamilyIndicesComplete(findQueueFamilies(device)) > 0;
}

Graphics::QueueFamilyIndices Graphics::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices = -1;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	int i = 0;
	for (const auto &queueFamily : queueFamilies) {
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

Graphics *createGraphics() {
	return new Graphics();
}

















