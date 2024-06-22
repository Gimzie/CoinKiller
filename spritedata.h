#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include <QList>
#include <QtXml>
#include <QTreeWidgetItem>
#include <QMap>
#include <QHash>

class Field
{
public:

    enum fieldType
    {
        List,
        Value,
        Checkbox,
        Bitfield
    };

    enum posType
    {
        Nybbles,
        Bits
    };

    Field() {}
    QString title;
    QString comment;
    fieldType type;
    int startPos;
    int endPos;
    posType posType;

    QList<QPair<int, QString>> listEntries;
    quint8 mask;
};

class SpriteDefinition
{
public:
    SpriteDefinition();
    SpriteDefinition(int spriteId);
    SpriteDefinition(QDomElement spriteElement);
    QString getName() const { return name; }
    int getID() const { return id; }
    QString getNotes() const { return notes; }
    Field* getFieldPtr(int id) { return &fields[id]; }
    int getFieldCount() const { return fields.size(); }
    void doOverride(const SpriteDefinition& other);

private:
    QString name;
    int id;
    QString notes;
    QList<Field> fields;
};

struct spriteCategory
{
    QList<int> sprites;
    QString name;
};

struct spriteView
{
    QString name;
    QList<spriteCategory> categories;
    QList<int> simpleSprites;
    QList<QTreeWidgetItem*> categoryNodes;
};

class SpriteData
{
public:
    SpriteData();
    int spriteViewCount() { return spriteViews.count(); }
    spriteView* spriteViewPtr(int view) { return &spriteViews[view]; }
    SpriteDefinition& getSpriteDef(int nbr);

    int spriteCount() { return spriteDefs.size(); }

    void loadSpriteDefs();
    void loadSpriteViews();

    QString getVersion() { return spriteDataVersion; }

private:
    QList<spriteView> spriteViews;
    QHash<int, SpriteDefinition> spriteDefs;

    bool customSprites = false;

    QString spriteDataVersion;
};

#endif // SPRITEDATA_H
