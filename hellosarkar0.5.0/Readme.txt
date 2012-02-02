There are at 10 or 11 installer for various platforms. For this app to work you must have proper Qt framework installed in your system. Since this app uses sqlite connection, you would also need qt sqlite packages if those are provided separately than the main framework.

The app may not work because of two problems:
    1. Qt Library not installed.
    2. The database file is not present in the expected location. The expected location of the database for various platform are:
        -for symbian "E:/hellosarkar/HelloSarkar.db"
        -for maemo and meego "/home/user/.hellosarkar/HelloSarkar.db"
        -for others "C:/myqt/hellosarkar/hellosarkar0.4.0/HelloSarkar.db"

Please note that the app has not been tested in all those hardwares and hence the app is likely to have UI issue. The situation can expected to be improved in coming versions.

Some other notes for my development purpose:
    GPS- not yet done
    Mobile number - I doubt its possible
    SMS Method - not yet implemented

    Kennel - what is that?
    ---How to get stat for complains sent as sms
    --send previously sending failed messages as well while updating
    -if connection problem ask to send sms or store locally only or delete

    --how to get stat, what is api?????????
    --http://apps.mobilenepal.net/hellosarkar/public/complain/getstatus
        -paras: response_code - unique id
            failure 0 - 400 or 500
            success solved - 200

    <mycomplaints>
        <complaints>
            <id>
            <name>
            <complainttype>
            <district>
            <detailaddress>
            <text>
            <date>
            <mobileno>
            <sentdatetime>
            <status>
            <gps>

    ToDo List
        -Scrollable Layout
        -Read Mobile Info and Mobile number and Coordinate from system
        -rotated version of the splash screen

    Done List:
        1 Requirements for the Hello Sarkar – Phase -I
        1.1 User must be allowed to submit the complaint. - done
        1.1.1 Must allow to enter the name of the complainer. Must not be Compulsory. - done
        1.1.2 Must allow to select the category the complaint. Must be compulsory. - done
        1.1.3 Must allow to select the district of the incident. Must be compulsory. - done
        1.1.4 Must allow to enter the detail address of the incident. Must be compulsory. - done
        1.1.5 Must allow to select the date of incident. If user does not select the date then current date must be default. - done
        1.1.6 Must allow to enter the detail description of the complaint. - done

        UI Scheme I - done

        Read xml - done

        Name - 15 Char max - done
        Detailed Address - 50 Char max - done
        Complain - 500 Char max - done

        -Splash Screen
        -Normal GUI
        -Post Data to web
        -Get code from web
        -Read district data and complain type from xml
        -Data validation
        -tackle different types of network code as listed in api


    //package dependencies for sqlite db in maemo
    -libqt4-sql
    -libqt4-sql-sqlite
    -libsqlite3-0
    -libsqlite3-dev this package may not be required or at least not available in default repo

    //    Response:
    //    6 digit alpha numeric UniqueIid For success along with respnose code 200
    //    For failure : 0 With response code 400 for invalid params and 503 for service unavailable



    Phases for Hellosarkar for Hackathon
    Phase 1

        a simple interface (name, category, district, detailed place, complaint) to send the complaint to the centralized server

        stores all the sent complaints locally

        choose to send the SMS if not connected

        ask users whether to send SMS or not, if not connected

        develop appropriate REST API (WEB)

        sendcomplaint (name, category, district, detailed place, complaint, mobile, datetime, GPS?)  returns the unique identifier to the mobile

    Phase 2

        simple web interface to enter the action taken for the complaints (WEB)

        add query option in mobile apps to query whether action is taken or not for the complaints, and display the status if action taken

        store results locally, with ability to see the details in future.

        develop appropriate REST API (WEB)

        querystatus (id) returns the status, else null if no action taken

    Phase 3

        ability to query for all the complaints and status based on criteria (category, district, date)

        store the results locally

        if status is "Action not taken", can query for the status at later date

        develop appropriate REST API (WEB)

        querycomplaints (category, district, dates) returns the lists of complaints

    Phase 4

        interactive maps functionality

        open data of the received complaints (maintaining anonymity)

        yet to explore (if we reach this phase)

