$("#runForm" ).submit(function( event ) {
	event.preventDefault();
	var $form = $( this );
	var term = $form.find( "input[id='cmd']" ).val();
	var url = $form.attr( "action" );
	// Send the data using post
	var posting = $.post( url, { cmd: term } );
	// Put the results in a div
	posting.done(function( data ) {
		$("#output").html(data);
	});
});