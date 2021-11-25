// Blockly.defineBlocksWithJsonArray([{
//     "type": "forward",
//     "message0": "Move Forward %1",
//     "args0": [
//         {
//             "type": "input_value",
//             "name": "hi"
//         }
//     ],
//     "inputsInline": false,
//     "colour": 120,
//     "tooltip": "",
//     "helpUrl": ""
// }]);

// Blockly.Blocks['testblock'] = {
//     init: function () {
//         this.appendDummyInput()
//             .appendField("Helloooo");
//         this.setPreviousStatement(true, null);
//         this.setNextStatement(true, null);
//         this.setColour(230);
//         this.setTooltip("");
//         this.setHelpUrl("");
//     }
// };


const directionArr = [];

Blockly.Blocks['forward'] = {
    init: function () {
        this.appendDummyInput()
            .appendField("Move Forward");
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(120);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.Blocks['stop'] = {
    init: function () {
        this.appendDummyInput()
            .appendField("Stop Car");
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(180);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.Blocks['turn'] = {
    init: function () {
        this.appendDummyInput()
            .appendField("Turn")
            .appendField(new Blockly.FieldDropdown([["Left 90°", "Motor_Left();\n"], ["Right 90°", "Motor_Right();\n"]]), "NAME");
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(330);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.Blocks['repeatuntilend'] = {
    init: function () {
        this.appendStatementInput("NAME")
            .setCheck(null)
            .appendField("Repeat Until End");
        this.setPreviousStatement(true, null);
        this.setColour(230);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.Blocks['print'] = {
    init: function () {
        this.appendDummyInput()
            .appendField("print")
            .appendField(new Blockly.FieldTextInput(""), "");
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(0);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.JavaScript['forward'] = function (block) {
    // TODO: Assemble JavaScript into code variable.
    var code = 'Motor_Start();\n';
    directionArr.push("1\n"); 
    return code;
};

Blockly.JavaScript['stop'] = function (block) {
    // TODO: Assemble JavaScript into code variable.
    var code = 'Motor_Stop();\n';
    directionArr.push("0\n"); 
    return code;
};

Blockly.JavaScript['turn'] = function (block) {
    var dropdown_name = block.getFieldValue('NAME');
    var result = dropdown_name.concat("\n");
    if(dropdown_name == "Motor_Left();\n"){
        directionArr.push("2\n"); 
    }else{
        directionArr.push("3\n"); 
    }
    // TODO: Assemble JavaScript into code variable.
    var code = 'Motor_Turn();\n';

    return dropdown_name;
};

Blockly.JavaScript['repeatuntilend'] = function (block) {
    var statements_name = Blockly.JavaScript.statementToCode(block, 'NAME');
    // TODO: Assemble JavaScript into code variable.
    var code = 'for(){\n};\n';
    return code;
};

Blockly.JavaScript['print'] = function (block) {
    // TODO: Assemble JavaScript into code variable.
    var code = 'uprintf();\n';
    return code;
};


// ////////////////////////////////////////////////////////////////////////
// Ported from terminal.js
var workspace = Blockly.inject('blocklyDiv',
{
    toolbox: document.getElementById('toolbox'
    ), trashcan: true
});

Blockly.Xml.domToWorkspace(document.getElementById('startBlocks'), workspace);


function illustrateCommand(){

}



// function showCode() {
// // Generate code and display it.
//     while (directionArr.length > 0) {
//         directionArr.pop();
//     }
//     result = "";

//     Blockly.JavaScript.INFINITE_LOOP_TRAP = null;
//     Blockly.JavaScript.addReservedWords('code');

//     var code = Blockly.JavaScript.workspaceToCode(workspace);

//     directionArr.forEach(function (entry) {
//         result = result.concat("", entry);
//     });
//     alert(result);
//     result = code.concat("\n", result);
//     document.getElementById('textArea').innerText = result;
// }

function clearCode() {
    document.getElementById('textArea').innerText = "";
}







// Blockly.JavaScript['print'] = function(block) {
//     // Search the text for a substring.
//     var operator = block.getFieldValue('END') == 'FIRST' ? 'indexOf' : 'lastIndexOf';
//     var subString = Blockly.JavaScript.valueToCode(block, 'FIND',
//         Blockly.JavaScript.ORDER_NONE) || '\'\'';
//     var text = Blockly.JavaScript.valueToCode(block, 'VALUE',
//         Blockly.JavaScript.ORDER_MEMBER) || '\'\'';
//     var code = text + '.' + operator + '(' + subString + ')';
//     return [code, Blockly.JavaScript.ORDER_FUNCTION_CALL];
//   };