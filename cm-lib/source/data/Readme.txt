This is the explanatory file for the data models

Note: Our Models are actually entities while data decorators are for the auto maintanance of the data members of
the entities means the model.
Each entity can contain child entities of its own like
    Client have 2 Contacts and 1 Address, so our entities are client, contact, and address but client has an individual
    entity of address while it has a collection of entities means more than one contacts.

We have implemented our entity class which can be inherited to implement our desired data model. Means we can make client
class by inheriting entity class which has all the functionalities, dynamic integration of datamembers and integrated saving
loading functionalities. Our entity class is also integrated with the addition of other entities as child entities of
that entity mean our main data model.

Why we do so ? = Because it provides a dynamic and structured way of programming and allow us to upgrade the application
anytime by the easy integration of other data members. It also helps to add some other comman functionalities to all of
our data models by simply adding it to our entity class.
