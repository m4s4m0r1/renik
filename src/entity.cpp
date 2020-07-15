#include <renik\cpp\entity.h>
namespace renik {
	namespace EntitySystem {
		//--BaseObject---
		template<class T> std::vector<Object<T>> Object<T>::m_objPool = std::vector<Object<T>>();
		template<class T> Object<T>::Object() {
			this->_active = true;
			this->_name = "Renik Object";
			this->_tags = std::vector<std::string>();
			this->_isApplied = false;
			this->_isPrepared = false;
			m_objPool.push_back(*this);
		}
		template<class T> Object<T>::~Object() {
			size_t s = m_objPool.size();
			for (size_t i = 0; i < s; i++) {
				if (&m_objPool[i] == this) {
					m_objPool.erase(m_objPool.begin() + i);
					break;
				}
			}
		}
		template<class T> bool Object<T>::get_active() { return _active; }
		template<class T> void Object<T>::set_active(bool value) { _active = value; }
		template<class T> std::string Object<T>::get_name() { return _name; }
		template<class T> void Object<T>::set_name(const std::string& value) { _name = value; }
		template<class T> void Object<T>::add_tag(const std::string& tag) { _tags.push_back(tag); }
		template<class T> const std::string* Object<T>::get_tags() { return _tags.data(); }
		template<class T> size_t Object<T>::get_tagsCount() { return _tags.size(); }
		template<class T> bool Object<T>::remove_tag(const std::string& tag) {
			auto len = _tags.size();
			for (size_t i = 0; i < len; i++) {
				if (_tags[i] == tag) {
					_tags.erase(_tags.begin() + i);
					return true;
				}
			}
			return false;
		}
		template<class T> void Object<T>::_setPrepared(bool state) { _isPrepared = state; }
		template<class T> void Object<T>::_setApplied(bool state) { _isApplied = state; }
		template<class T> void Object<T>::OnPrepare() { event_onPrepare(); _isPrepared = true; }
		template<class T> void Object<T>::OnApply() { event_onApply(); _isApplied = true; }

		//--Component--
		void* Component::get_entity() { return this->m_owner; }

		//--Entity--
		Entity::Entity() : Object() {
			this->m_comps = std::vector<Component>();
			this->m_scene = nullptr;
			this->m_parent = nullptr;
			this->m_childs = std::vector<Entity*>();
		}
		Component* Entity::add_component(const Component& comp) {
			if (comp._singleComponent) {
				size_t len = m_comps.size();
				for (size_t i = 0; i < len; i++)
				{
					if (m_comps[i]._typeName == comp._typeName) {
						return nullptr;
					}
				}
			}
			m_comps.push_back(comp);
			return &m_comps[m_comps.size() - 1];
		}
		Component* Entity::get_component(const std::string& typeName) {
			if (typeName.length() <= 0)
				return nullptr;
			size_t len = m_comps.size();
			for (size_t i = 0; i < len; i++) {
				if (m_comps[i]._typeName == typeName)
					return &m_comps[i];
			}
			return nullptr;
		}
		std::vector<Component*> Entity::get_components(const std::string& typeName) {
			std::vector<Component*> res;
			size_t len = m_comps.size();
			if (typeName.length() <= 0) {
				for (size_t i = 0; i < len; i++)
					res.push_back(&m_comps[i]);
			}
			else {
				for (size_t i = 0; i < len; i++)
				{
					if (m_comps[i]._typeName == typeName)
						res.push_back(&m_comps[i]);
				}
			}
			return res;
		}
		bool Entity::remove_component(Component* comp) {
			size_t len = m_comps.size();
			for (size_t i = 0; i < len; i++)
			{
				if (&m_comps[i] == comp)
				{
					m_comps.erase(m_comps.begin() + i);
					return true;
				}
			}
			return false;
		}
		void Entity::OnPrepare() {
			auto len = this->m_comps.size();
			for (size_t i = 0; i < len; i++) {
				if (this->m_comps[i].get_active())
					this->m_comps[i].OnPrepare();
			}
			Object<Entity>::OnPrepare();
		}
		void Entity::OnApply() {
			auto len = this->m_comps.size();
			for (size_t i = 0; i < len; i++)
			{
				if (this->m_comps[i].get_active())
					this->m_comps[i].OnApply();
			}
			Object<Entity>::OnApply();
		}

		Entity* Entity::get_parent() {
			return m_parent;
		}
		void Entity::set_parent(Entity* entity) {
			if (m_parent != nullptr) {
				size_t len = entity->m_childs.size();
				for (size_t i = 0; i < len; i++)
				{
					if (entity->m_childs[i] == this) {
						entity->m_childs.erase(entity->m_childs.begin() + i);
						break;
					}
				}
			}
			if (entity != nullptr) {
				entity->m_childs.push_back(this);
				m_parent = entity;
			}
		}
		Entity** Entity::get_childs() {
			return this->m_childs.data();
		}
		size_t Entity::get_childsCount() {
			return this->m_childs.size();
		}

		//--Scene--
		Scene::Scene() { this->m_entities = std::vector<Entity*>(); }
		bool Scene::add_entity(Entity* obj) {
			size_t len = m_entities.size();
			for (size_t i = 0; i < len; i++) {
				if (m_entities[i] == obj) {
					return false;
				}
			}
			m_entities.push_back(obj);
			obj->m_scene = this;
			return true;
		}
		bool Scene::remove_entity(Entity* obj) {
			size_t len = m_entities.size();
			for (size_t i = 0; i < len; i++)
			{
				if (m_entities[i] == obj) {
					m_entities.erase(m_entities.begin() + i);
					obj->m_scene = nullptr;
					return true;
				}
			}
			return false;
		}
		Entity** Scene::get_entities() {
			return m_entities.data();
		}
		size_t Scene::get_entitiesCount() {
			return m_entities.size();
		}
		void Scene::OnPrepare() {
			auto len = this->m_entities.size();
			for (size_t i = 0; i < len; i++)
			{
				if (this->m_entities[i]->get_active())
					this->m_entities[i]->OnPrepare();
			}
			Object<Scene>::OnPrepare();
		}
		void Scene::OnApply() {
			auto len = this->m_entities.size();
			for (size_t i = 0; i < len; i++)
			{
				if (this->m_entities[i]->get_active())
					this->m_entities[i]->OnApply();
			}
			Object<Scene>::OnApply();
		}
	}
}
