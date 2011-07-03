/*
 *  Copyright (c) 2011 Srikanth Tiyyagura <srikanth.tulasiram@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#include <QTest>
#include <QCoreApplication>

#include <qtest_kde.h>
#include <kactioncollection.h>
#include <kdebug.h>

#include "KoResourceTagging_test.h"
#include "KoResource.h"
#include "KoPattern.h"

void KoResourceTagging_test::testIntialization()
{
    m_tagObject = new KoResourceTagging("*.test");
    addData();
    /// Checking whether the readXMLFile works properly. Initially it should return NULL
    QCOMPARE(m_tagObject->getTagNamesList(), QStringList());
}

void KoResourceTagging_test::addData()
{
    /// data for testing
    m_resourceNames << "/home/.kde/testingResource.test" << "/home/.kde/resourceWithNoExtension";

    m_tags << "krita" << "krita_test";

}

void KoResourceTagging_test::testAddingDeletingTag()
{    
    /*
     * Adding Tags testing
     */
    /// first resourcename is general case
    KoResource* resource;
    resource = new KoPattern(m_resourceNames.at(0));
    m_tagObject->addTag(resource,m_tags.at(0));

    /// Second one is having no extension. This one calls getAdjustedFileNames()
    resource = new KoPattern(m_resourceNames.at(1));
    m_tagObject->addTag(resource,m_tags.at(1));

    QStringList tagsExp = m_tagObject->getTagNamesList();
    tagsExp.sort();
    /// checking whether m_tagList contains correct values using getTagNamesList()
    QCOMPARE( tagsExp, m_tags);

    for (int i =0 ; i< m_resourceNames.count() ; i++ ) {
        resource = new KoPattern(m_resourceNames.at(i));
        /// checks whether m_tagsRepo stores correctly by using getAssignedTagNamesList()
        QCOMPARE(m_tagObject->getAssignedTagsList(resource) , QStringList(m_tags.at(i)));
    }

    /// Checks whether already inserted tag again inserts into tagRepo or not
    resource = new KoPattern(m_resourceNames.at(0));
    m_tagObject->addTag(resource,m_tags.at(0));
    /// To check the above condition, we need to get the same values before and after insertion.
    QCOMPARE(m_tagObject->getAssignedTagsList(resource) , QStringList(m_tags.at(0)));

    /*
     * Deleting Tags testing
     */

    resource = new KoPattern(m_resourceNames.at(0));
    m_tagObject->delTag(resource,m_tags.at(0));
    /// Checking whether deleting tag works or not
    QCOMPARE(m_tagObject->getAssignedTagsList(resource) , QStringList());
    /// After deleting, m_tagsList should also remove the assigned tag
    QCOMPARE(m_tagObject->getTagNamesList() , QStringList(m_tags.at(1)));

    resource = new KoPattern(m_resourceNames.at(1));
    /// This pair is not exists, so there is no need to delete tag
    m_tagObject->delTag(resource,m_tags.at(0));
    QCOMPARE(m_tagObject->getAssignedTagsList(resource) , QStringList(m_tags.at(1)));
    /// After deleting, m_tagsList should also contains previous values
    QCOMPARE(m_tagObject->getTagNamesList() , QStringList(m_tags.at(1)));
}

void KoResourceTagging_test::testSearchingTag()
{
    KoResource* resource = new KoPattern(m_resourceNames.at(0));
    m_tagObject->addTag(resource, m_tags.at(0));

    m_tagObject->addTag(resource, m_tags.at(1));

    /// When tag is incomplete, the resources list will be empty
    QCOMPARE(m_tagObject->searchTag("kri"), QStringList());

    /// Testing when tag is given and sort() is used to make comparsion easy
    QStringList resourceNames = m_tagObject->searchTag(m_tags.at(1));
    resourceNames.sort();
    m_resourceNames.sort();
    QCOMPARE(resourceNames, m_resourceNames);

    /// Testing when more than one tag is given
    QCOMPARE(m_tagObject->searchTag(m_tags.at(1)+ ", "+ m_tags.at(0)), QStringList(m_resourceNames.at(1)));

    m_tagObject->delTag(resource,m_tags.at(1));

    /// Testing the function removeAdjustedFileNames()
    QCOMPARE(m_tagObject->searchTag(m_tags.at(1)), QStringList(m_resourceNames.at(0)));
}

void KoResourceTagging_test::testReadWriteXML()
{

    /// this will delete tagObject and also calls writeXML()
    m_tagObject->~KoResourceTagging();

    m_tagObject = new KoResourceTagging("*.test");

    /// Checking whether the readXMLFile works properly. getTagNamesList() should return m_tags
    QStringList tags = m_tagObject->getTagNamesList();
    tags.sort();
    QCOMPARE(tags, m_tags);

    KoResource* resource = new KoPattern(m_resourceNames.at(0));
    /// Checking whether the getAssingedTagsList() works properly after restart
    QCOMPARE(m_tagObject->getAssignedTagsList(resource), QStringList(m_tags.at(1)));

    m_tagObject->delTag(resource,m_tags.at(1));

    resource = new KoPattern(m_resourceNames.at(1));
    m_tagObject->delTag(resource,m_tags.at(0));

    m_tagObject->~KoResourceTagging();
}

QTEST_KDEMAIN(KoResourceTagging_test, GUI)

#include <KoResourceTagging_test.moc>
