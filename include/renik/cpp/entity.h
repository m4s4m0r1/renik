#pragma once
#ifndef RENIK_ENTITY_CPP_H
#include <renik\cpp\common.h>
namespace renik {
	namespace Entity {
		typedef RENFUNC(entityFunc, void);
		//--- BASE ENTITY OBJECT ---
		template<class T> class renikObject : public BaseObject<uint, T> {
		private:
			static std::vector<renikObject<T>> m_objPool;
		protected:
			bool _active;
			std::string _name;
			std::vector<std::string> _tags;
			bool _isPrepared;
			bool _isApplied;
			void _setPrepared(bool state);
			void _setApplied(bool state);
		public:
			renikObject();
			~renikObject();

			entityFunc ePrepare;
			entityFunc eApply;

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

		class renikComponent;
		class renikEntity;
		class renikScene;

		class renikComponent : public renikObject<renikComponent> {
		private:
			void* m_owner;
			friend class renikEntity;
		protected:
			bool _singleComponent;
			std::string _typeName;

		public:
			void* get_entity();
		};

		class renikEntity : public renikObject<renikEntity> {
		private:
			std::vector<renikComponent> m_comps;
			renikEntity* m_parent;
			std::vector<renikEntity*> m_childs;
			renikScene* m_scene;

			friend class renikScene;
		public:
			renikEntity();
			renikComponent* add_component(const renikComponent& comp);
			renikComponent* get_component(const std::string& typeName);
			std::vector<renikComponent*> get_components(const std::string& typeName);
			bool remove_component(renikComponent* comp);

			renikEntity* get_parent();
			void set_parent(renikEntity* entity);
			renikEntity** get_childs();
			size_t get_childsCount();

			void OnPrepare() override;
			void OnApply() override;
		};

		class renikScene : public renikObject<renikScene> {
		private:
			std::vector<renikEntity*> m_entities;
		public:
			renikScene();
			bool addObject(renikEntity* obj);
			bool removeObject(renikEntity* obj);
			renikEntity** getObjects();
			size_t getObjectsCount();

			void OnPrepare() override;
			void OnApply() override;
		};
	}
}

#endif // !RENIK_ENTITY_CPP_H
