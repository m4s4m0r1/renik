#pragma once
#ifndef RENIK_ENTITY_CPP_H
#define RENIK_ENTITY_CPP_H
#include <renik\cpp\common.h>
namespace renik {
	namespace EntitySystem {
		typedef RENFUNC(entityFunc, void);
		//--- BASE ENTITY OBJECT ---
		template<class T> class Object : public BaseObject<id_t, T> {
		private:
			static std::vector<Object<T>> m_objPool;
		protected:
			bool _active;
			std::string _name;
			std::vector<std::string> _tags;
			bool _isPrepared;
			bool _isApplied;
			void _setPrepared(bool state);
			void _setApplied(bool state);
		public:
			Object();
			~Object();

			entityFunc event_onPrepare;
			entityFunc event_onApply;

			virtual bool get_active();
			virtual void set_active(bool value);

			virtual std::string get_name();
			virtual void set_name(const std::string& value);

			virtual void add_tag(const std::string& tag);
			virtual bool remove_tag(const std::string& tag);
			virtual const std::string* get_tags();
			virtual size_t get_tagsCount();

			virtual void OnPrepare();
			virtual void OnApply();
		};

		class Component;
		class Entity;
		class Scene;

		class Component : public Object<Component> {
		private:
			void* m_owner;
			friend class Entity;
		protected:
			bool _singleComponent;
			std::string _typeName;

		public:
			void* get_entity();
		};

		class Entity : public Object<Entity> {
		private:
			std::vector<Component> m_comps;
			Entity* m_parent;
			std::vector<Entity*> m_childs;
			Scene* m_scene;

			friend class Scene;
		public:
			Entity();
			Component* add_component(const Component& comp);
			Component* get_component(const std::string& typeName);
			std::vector<Component*> get_components(const std::string& typeName);
			bool remove_component(Component* comp);

			Entity* get_parent();
			void set_parent(Entity* entity);
			Entity** get_childs();
			size_t get_childsCount();

			void OnPrepare() override;
			void OnApply() override;
		};

		class Scene : public Object<Scene> {
		private:
			std::vector<Entity*> m_entities;
		public:
			Scene();
			bool add_entity(Entity* obj);
			bool remove_entity(Entity* obj);
			Entity** get_entities();
			size_t get_entitiesCount();

			void OnPrepare() override;
			void OnApply() override;
		};
	}
}

#endif // !RENIK_ENTITY_CPP_H
