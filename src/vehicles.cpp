#include "vehicles.hpp"

namespace transport
{
	namespace vehicles
	{
		void Light::Parse(const nlohmann::json& json)
		{
			if (json.count("max_speed"))
				max_speed_ = json["max_speed"];
		}
		const Renderer::Texture& Light::GetTexture() const
		{
			return {};
		}
		double Light::GetSpeed() const
		{
			return max_speed_;
		}
		void Light::SetSpeed(const int speed)
		{
			max_speed_ = speed;
		}

		void Truck::Parse(const nlohmann::json& json)
		{
			if (json.count("max_speed"))
				max_speed_ = json["max_speed"];
			if (json.count("max_carrying_capacity"))
				max_carrying_capacity_ = json["max_carrying_capacity"];
		}
		const Renderer::Texture& Truck::GetTexture() const
		{
			return {};
		}
		double Truck::GetSpeed() const
		{
			return max_speed_ * (loaded_ / max_carrying_capacity_ + 0.5);	//max speed while empty, half of max speed while full
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

		void Passenger::Parse(const nlohmann::json& json)
		{
			if (json.count("max_speed"))
				max_speed_ = json["max_speed"];
			if (json.count("max_passenger"))
				max_passenger_ = json["max_passenger"];
		}
		const Renderer::Texture& Passenger::GetTexture() const
		{
			return {};
		}
		double Passenger::GetSpeed() const
		{
			return max_speed_;
		}
		void Passenger::AddPassenger(const int passenger_quan)
		{
			passenger_ += passenger_quan;
			if (passenger_ > max_passenger_)
			{
				passenger_ = max_passenger_;
			}
		}
		void Passenger::SubtractPassenger(const int passenger_quan)
		{
			passenger_ -= passenger_quan;
			if (passenger_ < 0)
			{
				passenger_ = 0;
			}
		}

		void IllegalRacer::Parse(const nlohmann::json& json)
		{
			if (json.count("max_speed"))
				Light::SetSpeed(json["max_speed"]);
		}
		const Renderer::Texture& IllegalRacer::GetTexture() const
		{
			return {};
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
			if (json.count("max_speed"))
				Light::SetSpeed(json["max_speed"]);
//			if (json.count("color"))
//				color_ = json["color"];
		}
		const Renderer::Texture& Colorful::GetTexture() const
		{
			return {};
		}
		double Colorful::GetSpeed() const
		{
			return Light::GetSpeed();
		}
		void Colorful::SetColor(const glm::vec4 color)
		{
			color_ = color;
		}

		void Police::Parse(const nlohmann::json& json)
		{
			if (json.count("max_speed"))
				Light::SetSpeed(json["max_speed"]);
		}
		const Renderer::Texture& Police::GetTexture() const
		{
			return {};
		}
		double Police::GetSpeed() const
		{
			return Light::GetSpeed();
		}

		void Tractor::Parse(const nlohmann::json& json)
		{
			if (json.count("max_speed"))
				max_speed_ = json["max_speed"];
		}
		const Renderer::Texture& Tractor::GetTexture() const
		{
			return {};
		}
		double Tractor::GetSpeed() const
		{
			return max_speed_;
		}
		void Tractor::SetStuffPerTick(const double stuff_per_tick)
		{
			stuff_per_tick_ = stuff_per_tick;
		}

	}
}
