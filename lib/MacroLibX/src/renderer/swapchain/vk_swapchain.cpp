/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vk_swapchain.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:22:28 by maldavid          #+#    #+#             */
/*   Updated: 2024/03/14 17:08:19 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <renderer/core/render_core.h>
#include <renderer/renderer.h>
#include <platform/window.h>
#include <SDL2/SDL_vulkan.h>
#include <algorithm>

namespace mlx
{
	void SwapChain::init(Renderer* renderer)
	{
		VkDevice device = Render_Core::get().getDevice().get();

		_renderer = renderer;
		_swapchain_support = querySwapChainSupport(Render_Core::get().getDevice().getPhysicalDevice());

		VkSurfaceFormatKHR surfaceFormat = renderer->getSurface().chooseSwapSurfaceFormat(_swapchain_support.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(_swapchain_support.present_modes);
		_extent = chooseSwapExtent(_swapchain_support.capabilities);

		std::uint32_t imageCount = _swapchain_support.capabilities.minImageCount + 1;
		if(_swapchain_support.capabilities.maxImageCount > 0 && imageCount > _swapchain_support.capabilities.maxImageCount)
			imageCount = _swapchain_support.capabilities.maxImageCount;

		Queues::QueueFamilyIndices indices = Render_Core::get().getQueue().findQueueFamilies(Render_Core::get().getDevice().getPhysicalDevice(), renderer->getSurface().get());
		std::uint32_t queueFamilyIndices[] = { indices.graphics_family.value(), indices.present_family.value() };

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = renderer->getSurface().get();
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = _extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.preTransform = _swapchain_support.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		if(indices.graphics_family != indices.present_family)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VkResult res = vkCreateSwapchainKHR(device, &createInfo, nullptr, &_swapchain);
		if(res != VK_SUCCESS)
			core::error::report(e_kind::fatal_error, "Vulkan : failed to create the swapchain, %s", RCore::verbaliseResultVk(res));

		std::vector<VkImage> tmp;
		vkGetSwapchainImagesKHR(device, _swapchain, &imageCount, nullptr);
		_images.resize(imageCount);
		tmp.resize(imageCount);
		vkGetSwapchainImagesKHR(device, _swapchain, &imageCount, tmp.data());

		for(std::size_t i = 0; i < imageCount; i++)
		{
			_images[i].create(tmp[i], surfaceFormat.format, _extent.width, _extent.height);
			_images[i].transitionLayout(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
			_images[i].createImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT);
		}

		_swapchain_image_format = surfaceFormat.format;
		#ifdef DEBUG
			core::error::report(e_kind::message, "Vulkan : created new swapchain");
		#endif
	}

	SwapChain::SwapChainSupportDetails SwapChain::querySwapChainSupport(VkPhysicalDevice device)
	{
		SwapChain::SwapChainSupportDetails details;
		VkSurfaceKHR surface = _renderer->getSurface().get();

		if(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities) != VK_SUCCESS)
			core::error::report(e_kind::fatal_error, "Vulkan : unable to retrieve surface capabilities");

		std::uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if(formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		std::uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if(presentModeCount != 0)
		{
			details.present_modes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.present_modes.data());
		}

		return details;
	}

	VkPresentModeKHR SwapChain::chooseSwapPresentMode([[maybe_unused]] const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		// in the future, you may choose to activate vsync or not
		return VK_PRESENT_MODE_IMMEDIATE_KHR;
	}

	VkExtent2D SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if(capabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max())
			return capabilities.currentExtent;

		int width, height;
		SDL_Vulkan_GetDrawableSize(_renderer->getWindow()->getNativeWindow(), &width, &height);

		VkExtent2D actualExtent = { static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) };

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}

	void SwapChain::recreate()
	{
		destroy();
		init(_renderer);
	}

	void SwapChain::destroy() noexcept
	{
		if(_swapchain == VK_NULL_HANDLE)
			return;
		vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		vkDestroySwapchainKHR(Render_Core::get().getDevice().get(), _swapchain, nullptr);
		_swapchain = VK_NULL_HANDLE;
		for(Image& img : _images)
			img.destroyImageView();
	}
}
