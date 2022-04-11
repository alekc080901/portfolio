'use strict';

const rl = require("readline-sync");
const fs = require("fs");

// ������������ ������ � ���� ������� � ����������� ������������ �����������
function stringifyNode(node) {
    if ("login" in node)
        return `Login: ${node.login}; Password: ${node.password}; Real name: ${node.name}`;

    else if ("size" in node)
        return `Name: ${node.name}; Size: ${node.size}; Date: ${node.date}`;
}

// ������� � ������� ���� ������ ������ �������� �� ������
function selectNode(lastNode) {
    if (!lastNode) {
        return null
    };

    let nodesArray = [];
    for (let node = lastNode; node != null; node = node.prev)
        nodesArray.push(stringifyNode(node));

    let position = rl.keyInSelect(nodesArray);
    if (position == -1)
        return null;
    return nodeFromPosition(lastNode, position);
}

// ���������� ������� ������ �� ��� ������� � ������
function nodeFromPosition(lastNode, position) {
    for (let node = lastNode, i = 0; node != null; node = node.prev, i++) {
        if (i == position)
            return node
    }
    throw "Position error";
}

// ������� ����� ����� ����� ���������� ������ �������
function makeLink(source, destination) {
    if (!source || !destination)
        return;
    source.links.push(destination);
    destination.links.push(source);
}

// ���������� ����� ����� ����� ���������� ������ ������� � ��������� ���� ��� ��������
function writeLinks(lastNode) {
    fs.writeFileSync("links.txt", ""); // ������� ����� ����� ��������������
    for (let node = lastNode; node != null; node = node.prev) {
        const linksArray = node.links;
        for (let linkedNode of linksArray) {
            fs.appendFileSync("links.txt", node.id);
            fs.appendFileSync("links.txt", ','); // ���������� �����������
            fs.appendFileSync("links.txt", linkedNode.id);
        }
    };
}

// ��������� ����� ����� ����� ���������� ������ ������� �� ���������� �����
function readLinks(firstNode, secondNode) {
    const linksArray = fs.readFileSync("links.txt").toString().split(',');

    for (let node = firstNode; node != null; node = node.prev) {
        const links = linksArray.filter((_, index, array) => array[index - 1] == node.id);

        node.links = links.map(id => { // ��������� ������ id ��������� ������ � ���� ��������
            for (let node = secondNode; node != null; node = node.prev)
                if (node.id == id) return node;
        })
    }

    for (let node = secondNode; node != null; node = node.prev) {
        const links = linksArray.filter((_, index, array) => array[index + 1] == node.id);

        node.links = links.map(id => {
            for (let node = firstNode; node != null; node = node.prev)
                if (node.id == id) return node;
        })
    }
}

// ������� ���������� ��������� id
function createId() {
    return Math.random().toString(36).substring(7)
}

// ������� ������� �� ������
function deleteNode(lastNode, deletionNode) {
    if (lastNode == deletionNode) { // ���� ��������� ������ ������ � ������
        lastNode = lastNode.prev;
        return;
    }
    for (let node = lastNode; node != null; node = node.prev) {
        if (node.prev == deletionNode & node.prev.prev == null) { // ���� ��������� ������ ��������� � ������
            node.prev = null;
            break;
        }

        if (node.prev == deletionNode) {
            node.prev = node.prev.prev;
            break;
        }
    }
}

// ������� ���������������� ����� ����� ����������
function freeMissedLinks(firstNode, secondNode) {
    deleteLinks(firstNode, secondNode);
    deleteLinks(secondNode, firstNode);

    function deleteLinks(node1, node2) {
        for (let sourceNode = node1; sourceNode != null; sourceNode = sourceNode.prev) {
            if (sourceNode.links.length) {
                sourceNode.links.forEach((item, index) => { if (!(item in list2Array(node2))) sourceNode.links.splice(index, 1) }); // ���� � ������� ���������������� ��������
            }
        }
    }
}

// ��������������� ������ � ������ ��������
function list2Array(lastNode) {
    let nodeArray = [];
    for (let node = lastNode; node != null; node = node.prev) {
        nodeArray.push(node);
    }
    return nodeArray;
}

// ��������������� ������ �������� � ������
function array2List(nodeArray) {
    let lastNode;

    for (let i = nodeArray.length-1; i > 0; i--) {
        lastNode = nodeArray[i];
        if (i == nodeArray.length-1) // ������� �������� ������������� null
            lastNode.prev = null;
        nodeArray[i-1].prev = lastNode;
    }
    lastNode = nodeArray[0]

    return lastNode;
}

// ��������� ������
function sortNodes(lastNode, param, order) {
    let nodeArray = list2Array(lastNode);
    nodeArray.sort((a, b) => {
        if (a[param] > b[param])
            return 1;
        if (a[param] < b[param])
            return -1;
        return 0;
    })

    if (!order)
        nodeArray.reverse()

    return array2List(nodeArray)
}

let lastUser = null;
let lastFile = null;

while (true) {
    let functionChoice = rl.keyInSelect([
        "Add user",
        "Add file",
        "Show information",
        "Link user and file",
        "Show all element links",
        "Save data",
        "Load data",
        "Delete element from lists",
        "Sort lists",
    ], "Enter your choice:",
        { cancel: "EXIT"});

    switch (functionChoice) {
        case (0): // ���������� ������ ������������ � ������
		const login = rl.question("Enter login: ");
		const password = rl.question("Enter password: ", { hideEchoBack: true });
		const realName = rl.question("Enter name: ");
            lastUser = { 
                login,
                password,
                name: realName,
                id: createId(),

                prev: lastUser,
                links: [],
            };
            break;

        case (1): // ���������� ������ ����� � ������
            const name = rl.question("Enter name: ");
            const size = Number(rl.question("Enter size: "));
            if (isNaN(size)) {
                console.log("Input the correct value of size (integer)!");
                break;
            }
            const date = Date(rl.question("Enter date: "));

            lastFile = {
                name,          
                size,
                date,
                id: createId(),

                prev: lastFile,
                links: [],
            };
            break;

        case (2): // ����� ���������� �� ����� �������
            console.log("USERS:");
            if (lastUser)
                for (let node = lastUser; node != null; node = node.prev)
                    console.log(stringifyNode(node))
            else
                console.log("List is empty!")

            console.log("FILES:");
            if (lastFile)
                for (let node = lastFile; node != null; node = node.prev)
                    console.log(stringifyNode(node))
            else
                console.log("List is empty!")
            break;

        case (3): // ���������� ����� ����� ������������� � ������
            console.log("CHOOSE USER");
            const selectedUser = selectNode(lastUser);
            if (!selectedUser)
                break;

            console.log("CHOOSE FILE");
            const selectedFile = selectNode(lastFile);
            makeLink(selectedFile, selectedUser);
            break;

        case (4): // ����� ������ � ���������� ��������
            const showChoice = rl.keyInSelect(["Users", "Files"], "Would you like to work with users or files?");
            if (showChoice == -1) break;
            const linksArray = showChoice == 0 ? selectNode(lastUser).links : selectNode(lastFile).links;

            if (!linksArray.length) {
                console.log("There are no links in this node.");
                break;
            }

            for (let linkedNode of linksArray)
                console.log(stringifyNode(linkedNode));
            break;

        case (5): // ���������� ���������� �� ������� � ���� 
            const jsonUser = JSON.stringify(lastUser, function (key, value) {
                return key == "links" ? undefined : value;
            });
            const jsonFile = JSON.stringify(lastFile, function (key, value) {
                return key == "links" ? undefined : value;
            });

            fs.writeFileSync("users.txt", jsonUser);
            fs.writeFileSync("files.txt", jsonFile);

            writeLinks(lastUser);
            break;

        case (6): // �������� ���������� � ������ �� �����
            lastUser = JSON.parse(fs.readFileSync("users.txt"));
            lastFile = JSON.parse(fs.readFileSync("files.txt"));

            readLinks(lastUser, lastFile);
            break;

        case (7): // �������� �������� �� ������
            const deletionChoice = rl.keyInSelect(["Users", "Files"], "Would you like to work with users or files?");
            if (deletionChoice == -1) break;
            const deletionNode = deletionChoice == 0 ? selectNode(lastUser) : selectNode(lastFile);

            if (!deletionNode) {
                console.log("Both lists are empty!");
                break;
            }

            deletionChoice == 0 ? deleteNode(lastUser, deletionNode) : deleteNode(lastFile, deletionNode);
            freeMissedLinks(lastUser, lastFile);
            break;

        case (8): // ���������� ������
            const listChoice = rl.keyInSelect(["Users", "Files"], "Would you like to work with users or files?");

            if (listChoice == 0) {
                const options = ["Login", "Password", "Name"];
                const paramChoice = rl.keyInSelect(options, "Choose the field of sorting:");
                if (paramChoice == -1) break;
                const ascChoice = rl.keyInYNStrict("Use ascending order?");
                sortNodes(lastUser, options[paramChoice].toLowerCase(), ascChoice)
            }
            else if (listChoice == 1) {
                const options = ["Name", "Size", "Date"];
                const paramChoice = rl.keyInSelect(options, "Choose the field of sorting:");
                if (paramChoice == -1) break;
                const ascChoice = rl.keyInYNStrict("Use ascending order?");
                sortNodes(lastFile, options[paramChoice].toLowerCase(), ascChoice)
            }
            else
                break;
            console.log("Sorting was successful!");
            break;

        case (-1):
            process.exit();
    }   
}
