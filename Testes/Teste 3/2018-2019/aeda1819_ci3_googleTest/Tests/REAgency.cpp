#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
    //do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
    this->properties = properties;
}

void REAgency::addProperty(Property* property) {
    this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
    this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
    return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
    PropertyTypeItem itemNotFound("", "", "", 0);
    BSTItrIn<PropertyTypeItem> it(catalogItems);
    while (!it.isAtEnd())
    {
        if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
            PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
            pti.setItems(it.retrieve().getItems());
            return pti;
        }
        it.advance();
    }
    return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
    PropertyTypeItem itemNotFound("", "","", 0);
    PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
    PropertyTypeItem ptiX = catalogItems.find(pti);
    if(ptiX == itemNotFound) {
        pti.addItems(property);
        this->catalogItems.insert(pti);
    }
    else {
        this->catalogItems.remove(ptiX);
        ptiX.addItems(property);
        this->catalogItems.insert(ptiX);
    }
    properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
    return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
    vector<ClientRecord> records;
    HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
    HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
    for(; it1 != it2; it1++) {
        records.push_back(*it1);
    }
    return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
    for(unsigned int i = 0; i < crs.size(); i++) {
        listingRecords.insert(crs[i]);
    }

}

priority_queue<Client> REAgency::getClientProfiles() const {
    return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
    clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    // A
    vector<Property*> toCat = {properties[0]};
    Property* aux = properties[0];
    int maxPrice = properties[0]->getPrice();
    for (int i = 1; i < properties.size(); i++) {
        if ((*aux).getAddress() != (*properties[i]).getAddress() ||aux->getPostalCode() != properties[i]->getPostalCode() ||aux->getTypology() != properties[i]->getTypology()) {
            PropertyTypeItem pti(aux->getAddress(),aux->getPostalCode(),aux->getTypology(),maxPrice);
            pti.setItems(toCat);
            catalogItems.insert(pti);
            toCat = { properties[i] };
            aux = properties[i];
            maxPrice = properties[i]->getPrice();
        }
        else {
            if (maxPrice < properties[i]->getPrice())
                maxPrice = properties[i]->getPrice();
            toCat.push_back(properties[i]);
        }
    }
    free(aux);
    toCat.clear();
}
vector<Property*> REAgency::getAvailableProperties(Property* property) const{
    vector<Property*> temp;
    BSTItrIn<PropertyTypeItem> it(catalogItems);
    while(!it.isAtEnd()){
        if(it.retrieve().getAddress()== property->getAddress()){
            if(it.retrieve().getPostalCode() == property->getPostalCode()){
                if(it.retrieve().getTypology() == property->getTypology()){
                    for (auto &p : it.retrieve().getItems()) {
                        tuple<Client *, int> aux = p->getReservation();
                        if (get<0>(aux) == NULL)//checks if its empty
                            temp.push_back(p);
                    }
                }
            }
        }
        it.advance();
    }
    return temp;
}


bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    BSTItrIn<PropertyTypeItem> it(catalogItems);
    vector<Property*> prop = getAvailableProperties(property);
    for (auto &p: prop){
        if(p-> getTypology() == property->getTypology() && p->getPostalCode() == property->getPostalCode() && p->getAddress() == property->getAddress()){
            client->addVisiting(p->getAddress(),p->getPostalCode(),p->getTypology(),to_string(p->getPrice()));
            int value = p->getPrice() * (100.0-percentage)/100.0;
            tuple<Client*, int> res (client,value);
            p->setReservation(res);
            return true;
        }
    }
    return false;

}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    //D

    listingRecords.insert(client);
}

void REAgency::deleteClients() {
    //E
    HashTabClientRecord::iterator it= listingRecords.begin();

    for(it; it!= listingRecords.end(); it++){
        if(get<0>(it->getClientPointer()->getVisiting()).empty()){
            it = listingRecords.erase(it);
        }


    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    // F


    vector<Client>::const_iterator it= candidates.begin();
    for (it; it != candidates.end(); it++){
        int number_reservations=0,number_visiting =(it)->getVisitedProperties().size();
        tuple<string,string,string,string> t("","","","");
        if(!((it)->getVisiting() == t)){
            number_visiting ++;
        }
        vector<Property*>::iterator it_p= properties.begin();
        for(it_p; it_p!= properties.end();it_p++){
            if((get<0>((*it_p)->getReservation()))->getEMail() == it->getEMail()){
                number_reservations++;
            }
        }
        if((number_reservations/number_visiting)>=min){
            clientProfiles.push(*it);
        }
    }


}

vector<Property*> REAgency::suggestProperties() {
    //TODO: G
    vector<Property*> tempProperties;

    return tempProperties;
}
