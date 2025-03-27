#include "vehicles.hpp"
#include "texture_loader.hpp"

namespace transport {
	namespace vehicles
	{
		void Light::Parse(const nlohmann::json& json)
		{
			if (json.contains("max_speed"))
				max_speed_ = json["max_speed"];
		}
		const Renderer::TextureHandle Light::GetTexture() const
		{
			static auto texture = TextureLoader::Load("textures/light.png");
			return texture;
		}
		double Light::GetSpeed() const
		{
			return max_speed_;
		}
		void Light::SetSpeed(const double speed)
		{
			max_speed_ = speed;
		}



		void Truck::Parse(const nlohmann::json& json)
		{
			if (json.contains("max_speed"))
				max_speed_ = json["max_speed"];
			if (json.contains("max_carrying_capacity"))
				max_carrying_capacity_ = json["max_carrying_capacity"];
		}
		const Renderer::TextureHandle Truck::GetTexture() const
		{
			static std::vector<Renderer::TextureHandle> textures
				{
					TextureLoader::Load("textures/truck0.png"),
					TextureLoader::Load("textures/truck1.png"),
					TextureLoader::Load("textures/truck2.png"),
					TextureLoader::Load("textures/truck3.png"),
					TextureLoader::Load("textures/truck4.png")
				};
			return textures[4 * loaded_ / max_carrying_capacity_];
		}
		double Truck::GetSpeed() const
		{
			return max_speed_ * (1 - 0.5 * loaded_ / max_carrying_capacity_);	//max speed while empty, half of max speed while full
		}
		void Truck::SetLoaded(const double cargo_mass)
		{
			if (cargo_mass > max_carrying_capacity_)
			{
				loaded_ = max_carrying_capacity_;
			}
			else 
			{
				loaded_ = cargo_mass;
			}
		}
		double Truck::GetLoaded() const
		{
			return loaded_;
		}
		double Truck::GetMaxCapacity() const
		{
			return max_carrying_capacity_;
		}
		std::optional<VertexType> Truck::GetNextVertexType() const
		{
			order_ = (++order_) % max_order_;
			std::cout << "order\t\t" << order_ << std::endl;
			return order_vec[order_];
		}



		void Passenger::Parse(const nlohmann::json& json)
		{
			if (json.contains("max_speed"))
				max_speed_ = json["max_speed"];
			if (json.contains("max_passenger"))
				max_passenger_ = json["max_passenger"];
		}

		const Renderer::TextureHandle Passenger::GetTexture() const
		{
			static std::vector<Renderer::TextureHandle> textures
				{
					TextureLoader::Load("textures/passenger0.png"),
					TextureLoader::Load("textures/passenger1.png"),
					TextureLoader::Load("textures/passenger2.png"),
					TextureLoader::Load("textures/passenger3.png"),
					TextureLoader::Load("textures/passenger4.png"),
					TextureLoader::Load("textures/passenger5.png"),
					TextureLoader::Load("textures/passenger6.png"),
					TextureLoader::Load("textures/passenger7.png"),
					TextureLoader::Load("textures/passenger8.png")
				};

			return textures[8*passenger_/max_passenger_];
		}

		double Passenger::GetSpeed() const
		{
			return max_speed_ * (1 - 0.5 * passenger_ / max_passenger_);
		}

		std::optional<VertexType> Passenger::GetNextVertexType() const
		{
			order_ = (++order_) % max_order_;
			return order_vec[order_];
		}


		void IllegalRacer::Parse(const nlohmann::json& json)
		{
			if (json.contains("max_speed"))
				IllegalRacer::SetSpeed(json["max_speed"]);
		}

		const Renderer::TextureHandle IllegalRacer::GetTexture() const
		{
			static auto texture = TextureLoader::Load("textures/illegal.png");
			return texture;
		}

		double IllegalRacer::GetSpeed() const
		{
			return Light::GetSpeed() * acceleration_;
		}

		void IllegalRacer::SetAcceleration(const double acceleration)
		{
			acceleration_ = acceleration;
		}



		void Colorful::Parse(const nlohmann::json& json)
		{
			Light::Parse(json);
			if (json.contains("color"))
			{
				color_[0] = json["color"][0];
				color_[1] = json["color"][1];
				color_[2] = json["color"][2];
			}
		}

		const Renderer::TextureHandle Colorful::GetTexture() const
		{
			static auto texture = TextureLoader::Load("textures/colorful.png");
			return texture;
		}

        glm::vec3 Colorful::GetColor() const
		{
			return color_;
		}

		void Colorful::SetColor(const glm::vec3 color)
		{
			color_ = color;
		}

		std::optional<VertexType> Colorful::GetNextVertexType() const
		{
			order_ = (++order_) % max_order_;
			return order_vec[order_];
		}


		
		void Police::Parse(const nlohmann::json& json)
		{
			if (json.contains("max_speed"))
				Light::SetSpeed(json["max_speed"]);
		}
		const Renderer::TextureHandle Police::GetTexture() const
		{
			static auto texture = TextureLoader::Load("textures/police.png");
			return texture;
		}
		double Police::GetSpeed() const
		{
			return Light::GetSpeed();
		}

		
		
		void Tractor::Parse(const nlohmann::json& json)
		{
			if (json.contains("max_speed"))
				max_speed_ = json["max_speed"];
			if (json.contains("stuff_per_tick"))
				stuff_per_tick_ = json["stuff_per_tick"];
		}
		const Renderer::TextureHandle Tractor::GetTexture() const
		{
			static auto texture = TextureLoader::Load("textures/tracktor.png");
			return texture;
		}
		double Tractor::GetSpeed() const
		{
			return max_speed_;
		}
		double Tractor::GetStuffPerTick() const
		{
			return stuff_per_tick_;
		}
		std::optional<VertexType> Tractor::GetNextVertexType() const
		{
			order_ = (++order_) % max_order_;
			return order_vec[order_];
		}

	}
}
