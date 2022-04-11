document.feedback.action = 'http://127.0.0.1:5000/server';
document.feedback.method = 'POST';

// document.feedback.onsubmit = (event) => {
//   event.preventDefault();

//   let obj = {};
//   var formData = new FormData(event.target);
//   formData.forEach((value, key) => obj[key] = value);

//   console.log(JSON.stringify(obj));

//   var xhr = new XMLHttpRequest();
//   xhr.open(event.target.method, event.target.action, true);
//   xhr.setRequestHeader("Content-Type", "application/json");
// //   xhr.setRequestHeader('Access-Control-Allow-Origin', '*');
//   var data = JSON.stringify(obj);
//   xhr.send(data);
// };

// document.feedback.submit();