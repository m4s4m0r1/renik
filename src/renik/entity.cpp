#ifdef RENIK_ENABLE
#include <renik\cpp\entity.h>
namespace renik {
	namespace Entity {
		//--BaseObject---
		template<class T> std::vector<renikObject<T>> renikObject<T>::m_objPool = std::vector<renikObject<T>>();
		template<class T> renikObject<T>::renikObject() {
			this->_active = true;
			this->_name = "Renik Object";
			this->_tags = std::vector<std::string>();
			this->_isApplied = false;
			this->_isPrepared = false;
			m_objPool.push_back(*this);
		}
		template<class T> renikObject<T>::~renikObject() {
			size_t s = m_objPool.size();
			for (size_t i = 0; i < s; i++) {
				if (&m_objPool[i] == this) {
					m_objPool.erase(m_objPool.begin() + i);
					break;
				}
			}
		}
		template<class T> bool renikObject<T>::get_active() { return _active; }
		template<class T> void renikObject<T>::set_active(bool value) { _active = value; }
		template<class T> std::string renikObject<T>::get_name() { return _name; }
		template<class T> void renikObject<T>::set_name(const std::string& value) { _name = value; }
		template<class T> void renikObject<T>::add_tag(const std::string& tag) { _tags.push_back(tag); }
		template<class T> const std::string* renikObject<T>::get_tags() { return _tags.data(); }
		template<class T> size_t renikObject<T>::get_tagsCount() { return _tags.size(); }
		template<class T> bool renikObject<T>::remove_tag(const std::string& tag) {
			auto len = _tags.size();
			for (size_t i = 0; i < len; i++) {
				if (_tags[i] == tag) {
					_tags.erase(_tags.begin() + i);
					return true;
				}
			}
			return false;
		}
		template<class T> void renikObject<T>::_setPrepared(bool state) { _isPrepared = state; }
		template<class T> void renikObject<T>::_setApplied(bool state) { _isApplied = state; }
		template<class T> void renikObject<T>::OnPrepare() { ePrepare(); _isPrepared = true; }
		template<class T> void renikObject<T>::OnApply() { eApply(); _isApplied = true; }

		//--renikComponent--
		void* renikComponent::get_entity() { return this->m_owner; }

		//--renikEntity--
		renikEntity::renikEntity() : renikObject() {
			this->m_comps = std::vector<renikComponent>();
			this->m_scene = nullptr;
			this->m_parent = nullptr;
			this->m_childs = std::vector<renikEntity*>();
		}
		renikComponent* renikEntity::add_component(const renikComponent& comp) {
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
		renikComponent* renikEntity::get_component(const std::string& typeName) {
			if (typeName.length() <= 0)
				return nullptr;
			size_t len = m_comps.size();
			for (size_t i = 0; i < len; i++) {
				if (m_comps[i]._typeName == typeName)
					return &m_comps[i];
			}
			return nullptr;
		}
		std::vector<renikComponent*> renikEntity::get_components(const std::string& typeName) {
			std::vector<renikComponent*> res;
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
		bool renikEntity::remove_component(renikComponent* comp) {
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
		void renikEntity::OnPrepare() {
			auto len = this->m_comps.size();
			for (size_t i = 0; i < len; i++) {
				if (this->m_comps[i].get_active())
					this->m_comps[i].OnPrepare();
			}
			renikObject<renikEntity>::OnPrepare();
		}
		void renikEntity::OnApply() {
			auto len = this->m_comps.size();
			for (size_t i = 0; i < len; i++)
			{
				if (this->m_comps[i].get_active())
					this->m_comps[i].OnApply();
			}
			renikObject<renikEntity>::OnApply();
		}

		renikEntity* renikEntity::get_parent() {
			return m_parent;
		}
		void renikEntity::set_parent(renikEntity* entity) {
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
		renikEntity** renikEntity::get_childs() {
			return this->m_childs.data();
		}
		size_t renikEntity::get_childsCount() {
			return this->m_childs.size();
		}

		//--renikScene--
		renikScene::renikScene() { this->m_entities = std::vector<renikEntity*>(); }
		bool renikScene::addObject(renikEntity* obj) {
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
		bool renikScene::removeObject(renikEntity* obj) {
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
		renikEntity** renikScene::getObjects() {
			return m_entities.data();
		}
		size_t renikScene::getObjectsCount() {
			return m_entities.size();
		}
		void renikScene::OnPrepare() {
			auto len = this->m_entities.size();
			for (size_t i = 0; i < len; i++)
			{
				if (this->m_entities[i]->get_active())
					this->m_entities[i]->OnPrepare();
			}
			renikObject<renikScene>::OnPrepare();
		}
		void renikScene::OnApply() {
			auto len = this->m_entities.size();
			for (size_t i = 0; i < len; i++)
			{
				if (this->m_entities[i]->get_active())
					this->m_entities[i]->OnApply();
			}
			renikObject<renikScene>::OnApply();
		}
	}
}
#endif //RENIK_ENABLE