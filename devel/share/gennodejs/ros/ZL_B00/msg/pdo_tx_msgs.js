// Auto-generated. Do not edit!

// (in-package ZL_B00.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class pdo_tx_msgs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.traction_position = null;
      this.traction_velocity = null;
      this.steer_position = null;
      this.steer_velocity = null;
    }
    else {
      if (initObj.hasOwnProperty('traction_position')) {
        this.traction_position = initObj.traction_position
      }
      else {
        this.traction_position = 0;
      }
      if (initObj.hasOwnProperty('traction_velocity')) {
        this.traction_velocity = initObj.traction_velocity
      }
      else {
        this.traction_velocity = 0;
      }
      if (initObj.hasOwnProperty('steer_position')) {
        this.steer_position = initObj.steer_position
      }
      else {
        this.steer_position = 0;
      }
      if (initObj.hasOwnProperty('steer_velocity')) {
        this.steer_velocity = initObj.steer_velocity
      }
      else {
        this.steer_velocity = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pdo_tx_msgs
    // Serialize message field [traction_position]
    bufferOffset = _serializer.int32(obj.traction_position, buffer, bufferOffset);
    // Serialize message field [traction_velocity]
    bufferOffset = _serializer.int32(obj.traction_velocity, buffer, bufferOffset);
    // Serialize message field [steer_position]
    bufferOffset = _serializer.int32(obj.steer_position, buffer, bufferOffset);
    // Serialize message field [steer_velocity]
    bufferOffset = _serializer.int32(obj.steer_velocity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pdo_tx_msgs
    let len;
    let data = new pdo_tx_msgs(null);
    // Deserialize message field [traction_position]
    data.traction_position = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [traction_velocity]
    data.traction_velocity = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [steer_position]
    data.steer_position = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [steer_velocity]
    data.steer_velocity = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ZL_B00/pdo_tx_msgs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4311f381460c7d703b7fe50387d84cb7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 traction_position
    int32 traction_velocity
    int32 steer_position
    int32 steer_velocity
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pdo_tx_msgs(null);
    if (msg.traction_position !== undefined) {
      resolved.traction_position = msg.traction_position;
    }
    else {
      resolved.traction_position = 0
    }

    if (msg.traction_velocity !== undefined) {
      resolved.traction_velocity = msg.traction_velocity;
    }
    else {
      resolved.traction_velocity = 0
    }

    if (msg.steer_position !== undefined) {
      resolved.steer_position = msg.steer_position;
    }
    else {
      resolved.steer_position = 0
    }

    if (msg.steer_velocity !== undefined) {
      resolved.steer_velocity = msg.steer_velocity;
    }
    else {
      resolved.steer_velocity = 0
    }

    return resolved;
    }
};

module.exports = pdo_tx_msgs;
